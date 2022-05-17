#pragma once
#include "League.h"
#include <string>

using namespace std;

class Player
{
private:
    unsigned int id;
    string name;
    int elo_p;
public:
    Player(unsigned int t_id, string n, int elo)
    : id(t_id), name(n), elo_p(elo){};

    Player(unsigned int t_id, string n)
    : id(t_id), name(n), elo_p(1000){};

    unsigned int get_id() const {return id;};
    string get_name() const {return name;};
    int get_elo() const {return elo_p;};
    void set_elo(unsigned int new_elo);
    void print();
};