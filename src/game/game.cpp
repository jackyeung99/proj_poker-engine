#include "game.hpp"
#include "player.hpp"
#include "bitmap.hpp"

#include <iostream> 
#include <vector>
#include <string>
#include <random>
#include <algorithm>


using namespace::std;

Game::Game() {
    add_players(player_cap, start_bb);

    // Ensure indexes are in range in case of two players
    this->dealer = dealer % players.size();
    this->sb = sb % players.size();
    this->bb = bb % players.size();
}
    
void Game::play_hand() {
    deck.reset_deck(); 
    
    // intitialize values
    int n = players.size();
    float pot_size = 0.0;
    vector<int> active_players(n, 1);
    CardBitmap community_cards;
    
    // Pre Round
    deal_players(deck);
    ante(pot_size);
    take_bets(active_players, pot_size, true);

    // main betting rounds
    turn_cards(3, deck , community_cards);
    take_bets(active_players, pot_size);
    turn_cards(1, deck , community_cards);
    take_bets(active_players, pot_size);
    turn_cards(1, deck , community_cards);

    for (const auto& p : players) {
        string hand = p.player_hand.to_string();
        cout << p.name << ' ' << hand <<'\n';
    }

    string hand = community_cards.to_string();
    cout <<  ' ' << hand <<'\n';

    

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

void Game::take_bets(vector<int>& active_players, float& potsize, bool is_pre_flop) {
    // start id is index of last action
    bool first_loop = true;
    
    int start_id = sb; 
    if (is_pre_flop){
        int start_id = (bb + 1) % players.size(); 
    } 

    int player_turn_idx = start_id;
    float bet_amount = 0;

    while ((player_turn_idx != start_id) & !first_loop ) {
        
        int action = players[player_turn_idx].action();
        
        player_turn_idx = (player_turn_idx + 1) % players.size();
        first_loop = false;
    }
    
}


void Game::turn_cards(int n, Deck& deck, CardBitmap& community_cards){
    
    for (int i=0; i<n; i++){
        int card = deck.draw_card();
        community_cards.add(card);
    }
    
}



// helpers
void Game::add_players(int n, int start_bb){
    
    for(int p=0; p<n ; p++){
        Player player;
        player.name = "Player_" + std::to_string(p); 
        player.balance = start_bb * bb ; 
        players.push_back(player);
        
    }
}

const std::vector<Player>& Game::get_players() const {
    return players;
}

void Game::evaluate_hands(){
}