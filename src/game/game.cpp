#include "game.hpp"
#include "player.hpp"
#include <iostream> 
#include <vector>
#include <string>
#include <random>
#include <algorithm>


using namespace::std;

Game::Game() {
    add_players(player_cap, start_bb);
}
    
void Game::play_hand() {
    Deck deck;
    int n = players.size();

    vector<int> active_players(n, 1);
    uint64_t community_cards = (1ULL << 52) - 1;;

    // vector<int> = deal_players(deck);
    float pot_size = pre_flop();




    rotate_blinds();
}


vector<int> Game::deal_players(Deck& deck) {
    int shift = 2;
    int n = players.size();
    
    vector<int> hands;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            int newIndex = (j + shift) % n;
            int card = deck.draw_card();
            hands.push_back(card);
            // players[newIndex].receive_card(card);
        }
    }

    return hands;
}

float Game::pre_flop() {
    float pot_size = 0.0;
    players[0].balance -= sb;
    players[1].balance -= bb;
    pot_size += sb + bb;
    return pot_size;
}

void Game::rotate_blinds(){
    // First player is small blind, second is big blind
    if (!players.empty()){
        Player sb = players.front();   
        players.erase(players.begin()); 
        players.push_back(sb);       
    }
}


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