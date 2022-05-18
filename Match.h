#pragma once

using namespace std;

template <typename T> class Match
{
private:
    unsigned int id;
    T* participant1;
    T* participant2;
    double winner;
public:
    Match(unsigned int m_id, T* p1, T* p2)
    : id(m_id), participant1(p1), participant2(p2), winner(){};

    Match(unsigned int m_id, T* p1, T* p2, double win)
    : id(m_id), participant1(p1), participant2(p2), winner(win) {};

    unsigned int get_id(){return id;};
    T* get_team_1(){return &participant1;};
    T* get_team_2(){return &participant2;};
    double get_winner(){return winner;};

    bool operator==(Match m1) {return id==m1.get_id();};
    bool operator!=(Match m1) {return not operator==(m1);};

};
