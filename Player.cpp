#include "Player.h"
#include <iostream>

using namespace std;

void Player::set_elo(unsigned int new_elo)
{
    elo_p = new_elo;
}


void Player::print()
{
    std::cout << "Player name: " << name << std::endl;
    std::cout << "Player id: " << id << std::endl;
    std::cout << "Player elo: " << elo_p << std::endl;
}

