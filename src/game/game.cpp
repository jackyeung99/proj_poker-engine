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
}
    
void Game::play_hand() {
    Deck deck;
    
    int n = players.size();
    
    vector<int> active_players(n, 1);
    CardBitmap community_cards;
    
    deal_players(deck);
    float pot_size = ante();
    
    for (const auto& p : players) {
        string hand = p.player_hand.to_string();
        cout << p.name << ' ' << hand <<'\n';
    }
    

    rotate_blinds();
}

float Game::ante() {
    float pot_size = 0.0;
    players[sb].balance -= blinds.first;
    players[bb].balance -= blinds.second;
    pot_size += blinds.first + blinds.second;
    return pot_size;
}

void Game::rotate_blinds(){
    // First player is small blind, second is big blind
    dealer = (dealer + 1) % players.size();
    sb = (sb + 1) % players.size();
    bb = (bb + 1) % players.size();
}

// rotational logic
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

void take_bets(int shift=2) {

}
        
void turn_cards(int n, Deck& deck){

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