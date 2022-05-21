#include "Team.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cmath>

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

void Team::recalculate_elo(unsigned int opp_elo, double match_score)
{
    if(match_score >= 0.0 && match_score <= 1)
    {
        double expected_score = 0.0;
        double expected_score_divider = 1.0 + pow(10, (((double)opp_elo - (double)elo_p) / 400.0));
        expected_score = 1.0 / expected_score_divider;
        double updated_elo = 0;
        updated_elo = static_cast<double>(elo_p) + 32.0 * (match_score - expected_score);
        this->set_elo(static_cast<int>(round(updated_elo)));
    } else {
        throw invalid_result;
    }
}

bool Team::operator==(Team const& other) const
{
    if(id == other.get_id())
        return true;
    else
        return false;
}

bool Team::operator<(Team const& other) const
{
    if(id < other.get_id())
        return true;
    else
        return false;
}

bool Team::operator>(Team const& other) const
{
    if(id > other.get_id())
        return true;
    else
        return false;
}