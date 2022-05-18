#include "Team.h"
#include <iostream>
#include <fstream>

using namespace std;

void Team::set_elo(unsigned int new_elo)
{
    elo_p = new_elo;
}

void Team::add_member(Player const& p1)
{
    team_members.push_back(p1);
    n_members++;
}

void Team::remove_member(unsigned int id)
{
    for(int i = 0; i < team_members.size(); i++)
    {
        if (team_members[i].get_id() == id)
        {
            team_members.erase(team_members.begin() + i);
            n_members--;
        }
    }
}


void Team::print() const
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

bool Team::operator==(Team const& other) const
{
    if(this->get_id() == other.get_id())
        return true;
    else
        return false;
}
