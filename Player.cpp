#include "Player.h"
#include <iostream>
#include <fstream>

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

void player_write(std::string file_name)
{
    std::ofstream file;
}


std::vector<Player> player_read(std::string file_name, int last_id)
// Template in file: "name", {elo pints}\n
// last_index - id of last player in our programm
{
    std::vector<Player> player_vect;
    std::ofstream file;
    std::string line;
    int id = last_id + 1;
    file.open(file_name);
    while(getline(std::cin, line))
    {
        std::string name = "";
        std::string elo_points = "";
        bool after = 0;
        for(int i; i<line.length(); i++)
        {
            if(line[i] != ',' and after == 0)
                name += line[i];
            else if(line[i] == ',')
                after = 1;
            else if (line[i] != ' ')
                elo_points += line[i];
        }
        Player* ptr = new Player(id, name, elo_points);

        id++;
    }

}

