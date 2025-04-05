#ifndef Game_H
#define Game_H

#include <vector> 
#include <player.hpp>
#include <deck.hpp>
#include <tuple>

class Game{
    public:
        Game(); 
        void play_hand();
        float ante();
        void rotate_blinds();
        
        void deal_players(Deck& deck);
        void take_bets(int shift=2);
        void turn_cards(int n, Deck& deck);

        void add_players(int player_cap, int start_bb);

        const std::vector<Player>& get_players() const; 
        

        
        // Game attributes
        int start_bb = 75;
        int player_cap = 2;
        std::pair<int, int> blinds = std::make_pair(1,2);

        // blinds index
        int dealer = 0;
        int sb = 1;
        int bb = 2;

    private:
        void evaluate_hands();
        std::vector<Player> players;
        
};


#endif