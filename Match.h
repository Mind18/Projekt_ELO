#pragma once
#include "Player.h"
#include "Team.h"

#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

enum match_result {Participant1, Participant2, Draw, TBD};
enum my_exceptions {illegal_result, invalid_participant, wrong_id, FileNotFoundError, FileError,
invalid_schedule};

template <typename T> class Match
{
private:
    unsigned int id;
    T participant1;
    T participant2;
    match_result result;
public:
    Match(unsigned int m_id, T p1, T p2)
    : id(m_id), participant1(p1), participant2(p2), result(TBD) {};

    Match(unsigned int m_id, T p1, T p2, match_result res)
    : id(m_id), participant1(p1), participant2(p2), result(res) {};

    unsigned int get_id() const {return id;};
    T get_participant_1() const {return participant1;};
    T get_participant_2() const {return participant2;};
    match_result get_result() const {return result;};
    void set_result(match_result new_result);
    double get_participant_result(T const& participant) const;
    void determine_winner(bool draw_allowed);

    bool operator==(Match const& other) const {
        return id==other.get_id() && participant1 == other.get_participant_1() && participant2 == other.get_participant_2();
        };
    bool operator!=(Match const& other) const {return !operator==(other);};

};