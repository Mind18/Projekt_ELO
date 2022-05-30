#include "Team.h"
#include "Player.h"
#include "Match.h"
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
        throw illegal_result;
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

std::vector<Team> team_read(std::string file_name, std::vector<Team> team_vect, unsigned int last_id)
// Template in file: "name": {elo points}, name_of_player, {player elo points}, ...\n
// last_index - id of last team in our programm
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
            std::vector<Player> player_vect;
            std::string team_name = "";
            std::string player_name = "";
            std::string elo_points = "";
            std::string pelo_points = "";
            bool after_team = 0;
            bool after_player = 0;
            int j = 0;
            int pid = 1;

            for(int i=0; i<line.size(); i++)
            {
                if(line[i] != ':' and after_team == 0)
                    team_name = team_name + line[i];
                else if(line[i] == ':')
                    after_team = 1;
                else if(after_team == 1 and line[i] != ',')
                    elo_points = elo_points + line[i];
                else if(line[i] == ',')
                {
                    j = i+1;
                    break;
                }
            }
            while (j<line.size())
            {
                if(line[j] != ',' and after_player == 0)
                    player_name = player_name + line[j];
                else if(line[j] == ',' and after_player == 0)
                    after_player = 1;
                else if(line[j] != ',' and after_player == 1)
                    pelo_points = pelo_points + line[j];
                else if(line[j] == ',' and after_player == 1)
                {
                    int pelo_int = stoi(pelo_points);
                    Player p1 (pid, player_name, pelo_int);
                    after_player = 0;
                    player_vect.push_back(p1);
                    player_name = "";
                    pelo_points = "";
                    pid++;
                }
                j++;
            }
            int pelo_int = stoi(pelo_points);
            Player p1 (pid, player_name, pelo_int);
            player_vect.push_back(p1);

            int elo_int = stoi(elo_points);
            Team t1 (id, team_name, player_vect, elo_int);
            team_vect.push_back(t1);
            id++;
        }
        file.close();
    }
    else {cout << "Unable to acces file: " << file_name << '\n';}
    return team_vect;
}