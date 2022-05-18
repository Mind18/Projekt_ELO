#pragma once
#include "Player.h"
#include <string>
#include <vector>

using namespace std;

class Team
{
private:
    unsigned int id;
    string name;
    vector <Player> team_members;
    unsigned int n_members;
    int elo_p;
public:
    Team(unsigned int t_id, string n, vector <Player> tm, int elo)
    : id(t_id), name(n), team_members(tm), n_members(tm.size()), elo_p(elo){};

    Team(unsigned int t_id, string n, vector <Player> tm)
    : id(t_id), name(n), team_members(tm), n_members(tm.size()), elo_p(1000){};

    unsigned int get_id() const {return id;};
    string get_name() const {return name;};
    vector<Player> get_members() {return team_members;};
    unsigned int get_n_members() {return n_members;};

    void add_member(Player const& p1);
    void remove_member(unsigned int id);

    int get_elo() const {return elo_p;};
    void set_elo(unsigned int new_elo);
    void recalculate_elo();

    void print();

    bool operator==(Team const& other);
    bool operator!=(Team const& other)
    {
        return !operator==(other);
    };
};