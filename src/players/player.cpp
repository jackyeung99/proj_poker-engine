#include "player.hpp"

#include <iostream> 
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <random> 

using namespace std;

int Player::action(){
    std::random_device rd; // Obtain a random seed from the OS
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

    // Define the range
    std::uniform_int_distribution<> distrib(1, 3); // Integer in range [1, 10]

    // Generate and print a random number
    return distrib(gen);
}


