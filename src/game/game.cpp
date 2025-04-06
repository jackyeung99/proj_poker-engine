#include "game.hpp"
#include "player.hpp"
#include "bitmap.hpp"

#include <iostream> 
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <numeric>


using namespace::std;
enum Stage { PRE_FLOP, FLOP, TURN, RIVER, SHOWDOWN }; 
enum Level { FOLD, CHECK, CALL, RAISE };

Game::Game() {
    add_players(player_cap, start_bb);

    // Ensure indexes are in range in case of two players
    this->dealer = dealer % players.size();
    this->sb = sb % players.size();
    this->bb = bb % players.size();
}
    
void Game::play_hand() {
    deck.reset_deck();

    int n = players.size();
    float pot_size = 0.0f;
    vector<int> active_players(n, 1);
    CardBitmap community_cards;

    // Pre-flop
    Stage stage = PRE_FLOP;
    take_bets(active_players, pot_size, stage == PRE_FLOP);

    const int deal_amounts[] = { 3, 1, 1 };
    const Stage stages[] = { FLOP, TURN, RIVER };

    for (int i = 0; i < 3; i++) {
        turn_cards(deal_amounts[i], deck, community_cards);
        stage = stages[i];

        bool all_all_in = true;
        for (size_t j = 0; j < players.size(); ++j) {
            if (active_players[j] && !players[j].is_all_in) {
                all_all_in = false;
                break;
            }
        }

        if (!all_all_in) {
            take_bets(active_players, pot_size, false);
        }

        if (is_hand_over(active_players, players, stage)) {
            break;
        }
    }

    if (stage == 'SHOWDOWN') {
        evaluate_hands(); 
    }
    
    assign_winnings();

    // Show players' hands
    for (const auto& p : players) {
        cout << p.name << " " << p.player_hand.to_string() << '\n';
    }

    cout << "Community Cards: " << community_cards.to_string() << '\n';

    rotate_blinds();
}


void Game::ante(float& pot_size) {
    players[sb].balance -= blinds.first;
    players[bb].balance -= blinds.second;
    pot_size += blinds.first + blinds.second;

}

void Game::rotate_blinds(){
    // First player is small blind, second is big blind
    dealer = (dealer + 1) % players.size();
    sb = (sb + 1) % players.size();
    bb = (bb + 1) % players.size();
}

// functions for all players 
void Game::deal_players(Deck& deck) {
    int shift = 2;
    int n = players.size();

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            int new_index = (j + shift) % n;
            int card = deck.draw_card();
            players[new_index].player_hand.add(card);
        }
    }
}

// FIX ME: all in 
void Game::take_bets(vector<int>& active_players, float& pot_size, bool is_pre_flop, vector<float>& player_bets) {
    bool first_loop = true;
    int start_id = is_pre_flop ? (bb + 1) % players.size() : sb;

    int player_turn_idx = start_id;
    float bet_amount = *max_element(player_bets.begin(), player_bets.end());

    bool betting_round_over = false;

    while (!betting_round_over) {
        if (active_players[player_turn_idx]) {
            process_player_action(player_turn_idx, pot_size, bet_amount, active_players, player_bets);
        }

        player_turn_idx = (player_turn_idx + 1) % players.size();
        first_loop = false;

        betting_round_over = true;
        for (size_t i = 0; i < players.size(); ++i) {
            if (active_players[i] && !players[i].is_all_in && player_bets[i] < bet_amount) {
                betting_round_over = false;
                break;
            }
        }

        if (accumulate(active_players.begin(), active_players.end(), 0) < 2) {
            break;
        }
    }
}

void Game::process_player_action(int player_id, float& pot_size, float& bet_size, vector<int>& active_players, vector<float>& player_bets) {
    float match_amount = bet_size - player_bets[player_id];
    Player& player = players[player_id];
    Level action = player.decide_action();

    switch (action) {
        case CHECK:
            if (player_bets[player_id] < match_amount) {
                active_players[player_id] = 0;
            }
            break;

        case CALL: {
            float call_amount = match_amount - player_bets[player_id];
            call_amount = min(call_amount, player.balance);

            player.balance -= call_amount;
            player_bets[player_id] += call_amount;
            pot_size += call_amount;

            if (player.balance == 0) {
                player.is_all_in = true;
            }
            break;
        }

        case FOLD:
            active_players[player_id] = 0;
            break;

        case RAISE: {
            float raise_amount = player.decide_raise_amount();
            raise_amount = min(raise_amount, player.balance);

            float total_bet = match_amount + raise_amount;

            float amount_to_call = total_bet - player_bets[player_id];

            player.balance -= amount_to_call;
            player_bets[player_id] = total_bet;
            pot_size += amount_to_call;

            bet_size = total_bet; 

            if (player.balance == 0) {
                player.is_all_in = true;
            }
            break;
        }

        default:
            break;
    }
}

void Game::turn_cards(int n, Deck& deck, CardBitmap& community_cards){
    
    for (int i=0; i<n; i++){
        int card = deck.draw_card();
        community_cards.add(card);
    }
    
}



// helpers
bool Game::is_hand_over(const vector<int>& active_players, const vector<Player>& players, int current_stage) {
    int active_count = accumulate(active_players.begin(), active_players.end(), 0);

    // Case 1: Only one player is left (everyone else folded)
    if (active_count <= 1) {
        return true;
    }


    // Case 2: If all players are all-in (no more betting possible)
    bool all_all_in = true;
    for (size_t i = 0; i < players.size(); i++) {
        if (active_players[i] && !players[i].is_all_in) {
            all_all_in = false;
            break;
        }
    }

    // Case 3: one player is all in and the other calls

    if (current_stage == RIVER) {
        return true;
    }

    return false; 
}

void Game::add_players(int n, int start_bb){
    
    for(int p=0; p<n ; p++){
        Player player;
        player.name = "Player_" + std::to_string(p);
        player.id = p; 
        player.balance = start_bb * bb ; 
        players.push_back(player);
        
    }
}

const std::vector<Player>& Game::get_players() const {
    return players;
}



void Game::assign_winnings(){

}
void Game::evaluate_hands(){
}