#include "League.h"
#include "Match.h"
#include "Player.h"
#include "Team.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <deque>

using namespace std;


template <typename T> T& League<T>::get_participant_by_id(unsigned int part_id)
{
    for(int i=0; i < participants.size(); i++)
    {
        if(participants[i].get_id() == part_id)
        {
            return participants[i];
        }
    }
    throw wrong_id;
};

template <typename T> match_result League<T>::simulate_match(unsigned int part_id, unsigned int part2_id, unsigned int last_match_id)
{
    Match <T> m1 (last_match_id + 1, get_participant_by_id(part_id),
    get_participant_by_id(part2_id));
    m1.determine_winner(this->get_draw_allowed());
    return m1.get_result();
}

template <typename T> match_result League<T>::simulate_match(Match<T> &match_to_simulate)
{
    match_to_simulate.determine_winner(this->get_draw_allowed());
    return match_to_simulate.get_result();
}

template <typename T> void League<T>::create_schedule()
{
    match_schedule.clear();
    unsigned int match_id = 1;
    size_t teams_to_pair;
    deque<T> rotating_teams;
    size_t part_size = participants.size();
    if(part_size == 0)
    {
        throw invalid_schedule;
    }
    T standing = participants[0];
    T having_bye = participants[part_size - 1];
    if(part_size % 2 == 1)
    {
        teams_to_pair = part_size - 1;
    } else {
        teams_to_pair = part_size;
    }

    for(size_t idx = 1; idx < teams_to_pair; idx++)
        rotating_teams.push_back(participants[idx]);

    size_t teams_rot = rotating_teams.size();
    for(size_t round = 0; round < teams_rot; round++)
    {
        Match<T> new_match = Match<T>(match_id, standing, rotating_teams[teams_rot - 1]);
        match_schedule.push_back(new_match);
        match_id++;
        for(size_t pair = 0; pair < teams_rot / 2; pair++)
        {
            T participant1 = rotating_teams[pair];
            T participant2 = rotating_teams[teams_rot - 2 - pair];
            new_match = Match<T>(match_id, participant1, participant2);
            match_schedule.push_back(new_match);
            match_id++;
        }
        if(part_size % 2 == 1)
        {
            rotating_teams.push_front(having_bye); // Currently highest index in queue -> teams_rot
            having_bye = rotating_teams[teams_rot]; // Currently highest index in queue -> teams_rot - 1
        } else {
            rotating_teams.push_front(rotating_teams[teams_rot - 1]);
        }
        rotating_teams.pop_back();
    }
}

template <typename T> void League<T>::print_standings()
{
    typename std::map<T, double>::iterator it = standings.begin();
    while (it != standings.end())
    {
        std::cout << "Participant: " << it->first.get_name() << " points: " << it->second << std::endl;
        it++;
    }
}

template <typename T> void League<T>::simulate_league(unsigned int rounds)
{
    /*
    1. Rozegraj mecz pomiędzy drużynami
    2. Dodaj drużynom punkty do tabeli na podstawie wyniku
    3. Zaaktualizuj druzynom note elo
    4. Powtorz dla kazdego meczu w schedule
    */

    cout << "League simulation\n\n";
    this->create_schedule();
    vector<Match <T>> schedule = this->get_match_schedule();
    for(int i = 0; i < rounds; i++)
    {
        for(size_t i = 0; i < schedule.size(); i++)
        {
            Match<T> match_to_play = schedule[i];
            T participant1 = match_to_play.get_participant_1();
            T participant2 = match_to_play.get_participant_2();
            unsigned int participant1_id = participant1.get_id();
            unsigned int participant2_id = participant2.get_id();
            match_result result = this->simulate_match(match_to_play); // Rozegraj mecz z terminarza
            if(result == Participant1) // Rozdaj punkty na bazie wyniku
            {
                standings[participant1] += get_pts_win();
                standings[participant2] += get_pts_lose();
            } else if(result == Participant2) {
                standings[participant2] += get_pts_win();
                standings[participant1] += get_pts_lose();
            } else if(result == Draw) {
                standings[participant1] += get_pts_draw();
                standings[participant2] += get_pts_draw();
            }
            // Dokonaj rekalkulacji elo na koniec meczu
            double patricipant1_result = match_to_play.get_participant_result(participant1);
            double patricipant2_result = match_to_play.get_participant_result(participant2);
            unsigned int participant1_elo = participant1.get_elo();
            unsigned int participant2_elo = participant2.get_elo();
            this->get_participant_by_id(participant1_id).recalculate_elo(participant2.get_elo(), patricipant1_result);
            this->get_participant_by_id(participant2_id).recalculate_elo(participant1.get_elo(), patricipant2_result);
        }
    }
    // Do testów usunąć na koniec
    // for (size_t i = 0; i < this->get_participants().size(); i++)
    // {
    //     T participant = this->get_participants()[i];
    //     cout << participant.get_name() << " elo points after league: " << participant.get_elo() << '\n';
    // }
}

template <typename T> void League<T>::clear_standings()
{
    for(int i = 0; i < participants.size(); i++)
    {
        standings[participants[i]] = 0;
    }
    return;
}

// template <typename T> map<T, map<int, int>> League<T>::monte_carlo_simulation(int iterations)
// {
//     vector<T> starting_participants = this->get_participants();
//     for ()
// }

template void League<Player>::simulate_league(unsigned int rounds);
template void League<Team>::simulate_league(unsigned int rounds);
template void League<Player>::create_schedule();
template void League<Team>::create_schedule();
template Team& League<Team>::get_participant_by_id(unsigned int part_id);
template Player& League<Player>::get_participant_by_id(unsigned int part_id);
template void League<Team>::print_standings();
template void League<Player>::print_standings();
template match_result League<Team>::simulate_match(unsigned int part_id, unsigned int part2_id, unsigned int last_match_id);
template match_result League<Player>::simulate_match(unsigned int part_id, unsigned int part2_id, unsigned int last_match_id);
template match_result League<Team>::simulate_match(Match<Team> &match_to_simulate);
template match_result League<Player>::simulate_match(Match<Player> &match_to_simulate);
template void League<Player>::clear_standings();
template void League<Team>::clear_standings();
