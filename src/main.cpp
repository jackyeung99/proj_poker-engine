#include "deck.hpp"
#include "game.hpp"
#include <iostream> 
#include <vector>


int main(){


    Game game;
    for (const auto&player : game.getPlayers()){
        std::cout << player.name << "Has balance $" <<player.balance << std::endl;
    }

    game.play_hand();

    for (const auto&player : game.getPlayers()){
        std::cout << player.name << "Has balance $" <<player.balance << std::endl;
    }
    game.play_hand();

    return 0;
}