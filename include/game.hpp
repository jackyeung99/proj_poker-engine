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
        void ante(float& pot_size);
        void rotate_blinds();
        
        void deal_players(Deck& deck);
        void take_bets(std::vector<int>& active_players, float& potsize, bool is_pre_flop=false, std::vector<float>& player_bets);
        void process_player_action(int player_id, float& pot_size, float& bet_size, std::vector<int>& active_players, std::vector<float>& player_bets);
        void turn_cards(int n, Deck& deck, CardBitmap& community_cards);

        void assign_winnings();
        void add_players(int player_cap, int start_bb);
        const std::vector<Player>& get_players() const; 
        bool is_hand_over(const std::vector<int>& active_players, const vector<Player>& players, int current_stage);

        
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
        Deck deck;
        
};


#endif 