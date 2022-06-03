#pragma once
#include "League.h"
#include <string>

using namespace std;

class Player
{
private:
    unsigned int id;
    string name;
    unsigned int elo_p;
public:
    Player(unsigned int t_id, string n, int elo)
    : id(t_id), name(n), elo_p(elo){};

    Player(unsigned int t_id, string n)
    : id(t_id), name(n), elo_p(1000){};

    unsigned int get_id() const {return id;};
    string get_name() const {return name;};
    unsigned int get_elo() const {return elo_p;};
    void set_elo(unsigned int new_elo);
    void recalculate_elo(unsigned int opp_elo, double match_score);
    void print() const;

    bool operator==(Player const& other) const;
    bool operator!=(Player const& other) const
    {
        return !operator==(other);
    }
    bool operator<(Player const& other) const;
    bool operator>(Player const& other) const;
};

void player_write(std::string file_name, std::vector<Player> player_vect);
std::vector<Player> player_read(std::string file_name, std::vector<Player> player_vect, unsigned int last_id);