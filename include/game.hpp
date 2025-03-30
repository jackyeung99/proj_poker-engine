#ifndef Game_H
#define Game_H

#include <vector> 
#include <player.hpp>

class Game{
    public:
        Game(); 
        void play_hand();
        void deal_players();
        void turn_cards(int n);
        void take_bets();
        void rotate_blinds();
        const std::vector<Player>& getPlayers() const; 

        void add_players(int player_cap, int start_bb);
        
        int start_bb = 75;
        int player_cap = 2;
        float bb = 2;
        float sb = 1;

    private:
        // Amount of bb player starts with 
        void evaluate_hands();
        std::vector<Player> players;
    
};


#endif