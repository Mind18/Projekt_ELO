#include "Team.h"
#include <iostream>
#include <fstream>

using namespace std;

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
    cout << "Team name: " << name << endl;
    cout << "Team id: " << id << endl;
    cout << "Team elo: " << elo_p << endl;
    cout << "Team " << name << " members:\n" << endl;
    for (int i = 0; i < team_members.size(); i++)
    {
        team_members[i].print();
        cout << '\n';
    }
}
