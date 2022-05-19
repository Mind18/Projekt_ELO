#pragma once
#include "Match.h"

#include<iostream>
#include<vector>
#include<map>
#include<fstream>

using namespace std;

template <typename T> class League
{
private:
    unsigned int id;
    std::vector<T> Participants;
    std::vector<Match <T>> match_schedule;
    std::map<T, double> standings;
    double pts_win;
    double pts_draw;
    double pts_lose;
    bool is_draw_allowed;
public:
    League(unsigned int l_id, vector<T> members, vector<Match<T>> matches,
    std::map<T, double> table, double win, double draw, double lose,  bool draw_allow)
    : id(l_id), Participants(members), match_schedule(matches), standings(table), pts_win(win),
    pts_lose(lose), pts_draw(draw_allow ? draw : 0), is_draw_allowed(draw_allow){};

    unsigned int get_id(){return id;};
    vector <T> get_participants(){return Participants;};
    vector<Match <T>> get_match_schedule(){return match_schedule;};
    double get_pts_win(){return pts_win;}
    double get_pts_draw(){return pts_draw;}
    double get_pts_lose(){return pts_lose;}

    void set_schedule(vector<Match <T>> new_match_schedule){match_schedule = new_match_schedule;};

};
