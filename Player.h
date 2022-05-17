#pragma once
#include "League.h"
#include <string>

class Player
{
private:
    unsigned int id;
    std::string name;
    int elo_p;
public:
    Player(unsigned int t_id, std::string n, int elo)
    : id(t_id), name(n), elo_p(elo){};

    Player(unsigned int t_id, std::string n)
    : id(t_id), name(n), elo_p(1000){};

    unsigned int get_id() const {return id;};
    std::string get_name() const {return name;};
    int get_elo() const {return elo_p;};
    void set_elo(unsigned int new_elo);
    void print();
};