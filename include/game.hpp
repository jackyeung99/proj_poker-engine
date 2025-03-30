#ifndef Game_H
#define Game_H

#include <vector> 

class Game{
    public:
        void play_hand();
        void deal_players();
        void turn_cards(int n);
        void take_bets();

        float bb = 2;
        float sb = 1;

    private:
        int player_cap = 2;
        void add_players();
        void evaluate_hands();
        // vector<Player> players;
    
};


#endif