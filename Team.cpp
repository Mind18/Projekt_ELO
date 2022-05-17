#include "Team.h"
#include <iostream>

void Team::add_member(Player const& p1)
{
    team_members.push_back(p1);
}

void Team::set_elo(unsigned int new_elo)
{
    elo_p = new_elo;
}

void Team::print()
{
    std::cout << "Team name: " << name << std::endl;
    std::cout << "Team id: " << id << std::endl;
    std::cout << "Team elo: " << elo_p << std::endl;
    std::cout << "Team members: " << name << std::endl;
    for (int i = 0; i < team_members.size(); i++)
    {
        team_members[i].print();
    }

}