#pragma once
#include "Player.h"
#include <string>
#include <vector>

class Team
{
private:
    unsigned int id;
    std::string name;
    std::vector <Player> team_members;
    int elo_p;
public:
    Team(unsigned int t_id, std::string n, std::vector <Player> tm, int elo)
    : id(t_id), name(n), team_members(tm), elo_p(elo){};

    Team(unsigned int t_id, std::string n, std::vector <Player> tm)
    : id(t_id), name(n), team_members(tm), elo_p(1000){};

    unsigned int get_id() const {return id;};
    std::string get_name() const {return name;};
    int get_elo() const {return elo_p;};
    void add_member(Player const& p1);
    void set_elo(unsigned int new_elo);
    void print();
};