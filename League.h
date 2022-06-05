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
    std::vector<T> participants;
    std::vector<Match <T>> match_schedule;
    std::map<T, double> standings;
    double pts_win;
    double pts_draw;
    double pts_lose;
    bool is_draw_allowed;
public:
    League(unsigned int l_id, vector<T> members, vector<Match<T>> matches,
    std::map<T, double> table, double win, double draw, double lose,  bool draw_allow)
    : id(l_id), participants(members), match_schedule(matches), standings(table), pts_win(win),
    pts_lose(lose), pts_draw(draw_allow ? draw : 0), is_draw_allowed(draw_allow){};

    unsigned int get_id(){return id;};
    vector <T> get_participants(){return participants;};

    vector<Match <T>> get_match_schedule(){return match_schedule;};
    double get_pts_win(){return pts_win;};
    double get_pts_draw(){return pts_draw;};
    double get_pts_lose(){return pts_lose;};
    bool get_draw_allowed(){return is_draw_allowed;};

    void set_pts_win(int win_points){pts_win = win_points;};
    void set_pts_draw(int draw_points){pts_draw = draw_points;};
    void set_pts_lose(int lose_points){pts_lose = lose_points;};
    void set_draw_allowed(bool allow_draw){is_draw_allowed = allow_draw;};
    void set_participants(vector<T> new_participants){participants = new_participants;};

    T& get_participant_by_id(unsigned int part_id);

    void set_schedule(vector<Match <T>> new_match_schedule){match_schedule = new_match_schedule;};

    match_result simulate_match(unsigned int part_id, unsigned int part2_id, unsigned int last_match_id);
    match_result simulate_match(Match<T> &match_to_simulate);

    void simulate_league();
    void create_schedule();

    void read_schedule();

    void aquire_participants();

    void print_standings();
};
