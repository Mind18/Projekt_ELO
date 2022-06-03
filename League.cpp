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


template <typename T> T League<T>::get_participant_by_id(unsigned int part_id)
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

template <typename T> double League<T>::simulate_match(unsigned int part_id, unsigned int part2_id, unsigned int last_match_id)
{
    Match <T> m1 (last_match_id + 1, get_participant_by_id(part_id),
    get_participant_by_id(part2_id));
    return m1.get_participant_result(m1.get_participant_1());
}

template <typename T> void League<T>::create_schedule()
{
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

template <typename T> void League<T>::simulate_league()
{
    cout << "League simulation\n";
}

template void League<Player>::simulate_league();
template void League<Team>::simulate_league();
template void League<Player>::create_schedule();
template void League<Team>::create_schedule();
template Team League<Team>::get_participant_by_id(unsigned int part_id);
template Player League<Player>::get_participant_by_id(unsigned int part_id);
template void League<Team>::print_standings();
template void League<Player>::print_standings();
template double League<Team>::simulate_match(unsigned int part_id, unsigned int part2_id, unsigned int last_match_id);
template double League<Player>::simulate_match(unsigned int part_id, unsigned int part2_id, unsigned int last_match_id);
