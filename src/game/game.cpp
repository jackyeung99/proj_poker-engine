#include <iostream> 
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "game.hpp"


using namespace::std;

Game::Game() {
    add_players(player_cap, start_bb);
}
    
void Game::play_hand() {
    float pot_size = 0.0;
    pot_size += sb + bb;
    players[0].balance -= sb; 
    players[1].balance -= bb;
    

    rotate_blinds();
}


void Game::rotate_blinds(){
    // First player is small blind, second is big blind
    if (!players.empty()){
        Player sb = players.front();   
        players.erase(players.begin()); 
        players.push_back(sb);       
    }
}

void Game::deal_players(){
}

void Game::turn_cards(int n){

}


void Game::take_bets(){
}

void Game::add_players(int n, int start_bb){

    for(int p=0; p<n ; p++){
        Player player;
        player.name = "Player_" + std::to_string(p); 
        player.balance = start_bb * bb ; 
        players.push_back(player);

    }
}

const std::vector<Player>& Game::getPlayers() const {
    return players;
}

void Game::evaluate_hands(){
}