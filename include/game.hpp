#ifndef Game_H
#define Game_H

#include <vector> 
#include <player.hpp>
#include <deck.hpp>

class Game{
    public:
        Game(); 
        void play_hand();
        float pre_flop();
        void turn_cards(int n, Deck deck);
        void take_bets();
        void rotate_blinds();
        
        std::vector<int> deal_players(Deck& deck);

        void add_players(int player_cap, int start_bb);

        const std::vector<Player>& get_players() const; 
        

        
        // Amount of bb player starts with 
        int start_bb = 75;
        int player_cap = 2;
        float bb = 2;
        float sb = 1;

    private:
        void evaluate_hands();
        std::vector<Player> players;
        Deck deck;
        
};


#endif