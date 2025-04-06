#include "player.hpp"

#include <iostream> 
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <random> 

using namespace std;
enum Level { FOLD, CHECK, CALL, RAISE };

Level Player::decide_action() {
    std::random_device rd; 
    std::mt19937 gen(rd()); 

    // Range: 0 = FOLD, 1 = CHECK, 2 = CALL, 3 = RAISE
    std::uniform_int_distribution<> distrib(0, 3); 

    int action = distrib(gen);
    return static_cast<Level>(action);
}


float Player::decide_raise_amount(){
    return 0.0f;
}


