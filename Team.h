#pragma once
#include "League.h"

class Team
{
private:
    unsigned int id;
public:
    Team(unsigned int t_id) : id(t_id){};
    ~Team();
};