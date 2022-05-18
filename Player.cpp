#include "Player.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void Player::set_elo(unsigned int new_elo)
{
    elo_p = new_elo;
}

void Player::recalculate_elo()
{
    //code here
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


void player_read(std::string file_name, std::vector<Player> player_vect, unsigned int last_id)
// Template in file: "name", {elo pints}\n
// last_index - id of last player in our programm
{
    std::ifstream file;
    unsigned int id = last_id + 1;
    file.open(file_name, ios::out | ios::app);
    if(file.good() == false){cout << "File does not exist\n"; throw FileNotFoundError;}
    if(file.is_open())
    {
        std::string line;
        while(getline(file, line))
        {
            std::string name = "";
            std::string elo_points = "";
            bool after = 0;
            for(int i; i<line.size(); i++)
            {
                if(line[i] != ',' and after == 0)
                    name += line[i];
                else if(line[i] == ',')
                    after = 1;
                else if(line[i] != ' ')
                    elo_points += line[i];
            }
            Player p1 (id, name, stoi(elo_points));
            player_vect.push_back(p1);
            id++;
        }
    file.close();
    }
    else {cout << "Unable to acces file: " << file_name << '\n';}

    cout << '\n';
    player_vect[0].print();
    cout << player_vect.size();
}

