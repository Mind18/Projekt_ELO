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
    T get_participant_by_id(unsigned int part_id)
    {
    for(int i=0; i < Participants.size(); i++)
    {
        if(Participants[i].get_id() == part_id)
        {
            return Participants[i];
        }
    }
    throw wrong_id;
    };
    vector<Match <T>> get_match_schedule(){return match_schedule;};
    double get_pts_win(){return pts_win;};
    double get_pts_draw(){return pts_draw;};
    double get_pts_lose(){return pts_lose;};

    void set_schedule(vector<Match <T>> new_match_schedule){match_schedule = new_match_schedule;};

    double simulate_match(unsigned int part_id, unsigned int part2_id, unsigned int last_match_id)
    {
        unsigned int m_id = last_match_id + 1;
        Match <T> m1 (m_id, get_participant_by_id(part_id),
        get_participant_by_id(part2_id));
        return m1.get_participant_result(m1.determine_winner(/*code here*/));
    }
    void simulate_league();
    void create_schedule(bool rematch)
    {
        for(int i=Participants.size()-1; i>=0; i--)
        {
            for(int j=i-1; j>=0; j--)
            {
                continue;
            }
            std::cout << "ok\n";
        }
    }

    void read_schedule();

    void aquire_participants();

    void print_standings()
    {
        typename std::map<T, double>::iterator it = standings.begin();
        while (it != standings.end())
        {
            std::cout << "Participant: " << it->first.get_name() << " points: " << it->second << std::endl;
            it++;
        }
    }
};
