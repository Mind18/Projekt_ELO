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

};
