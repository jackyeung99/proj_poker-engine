#ifndef player_H
#define player_H

#include <string> 
#include <vector> 

class Player{
    public:
        std::string name; 
        float balance = 0;
        int action();
        void reset_hand();
        uint64_t hand_bitmap; 


        Player(){
            hand_bitmap = (1ULL << 52) - 1;
        }

    private:

};

#endif