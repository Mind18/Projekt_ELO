#include "Match.h"
#include "Player.h"
#include "Team.h"
#include <iostream>
#include <random>
#include <chrono>

template <typename T> void Match<T>::set_result(match_result new_result)
{
    result = new_result;
}

template <typename T> double Match<T>::get_participant_result(T const& participant) const
{
    if (participant != participant1 && participant != participant2)
    {
        throw invalid_participant;
    } else {
        if (result == Draw)
        {
            return 0.5;
        } else if (result == Participant1) {
            if (participant == participant1)
            {
                return 1.0;
            } else {
                return 0.0;
            }
        } else if (result == Participant2) {
            if (participant == participant2)
            {
                return 1.0;
            } else {
                return 0.0;
            }
        } else {
            throw illegal_result;
        }
    }
}

template <typename T> void Match<T>::determine_winner(bool draw_allowed)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    std::normal_distribution<double> participant1_distribution(participant1.get_elo(), 256);
    std::normal_distribution<double> participant2_distribution(participant2.get_elo(), 256);

    double participant1_result = participant1_distribution(generator);
    double participant2_result = participant2_distribution(generator);
    std::cout << participant1.get_name() << " score: " << participant1_result << '\n';
    std::cout << participant2.get_name() << " score: " << participant2_result << '\n';
    std::cout << '\n';
    if(participant1_result > participant2_result) {
        this->set_result(Participant1);
        return;
    } else if(participant2_result > participant1_result) {
        this->set_result(Participant2);
        return;
    } else if(participant1_result == participant2_result){
        if(draw_allowed)
        {
            this->set_result(Draw);
            return;
        } else {
            determine_winner(draw_allowed);
            return;
        }
    }
}

template void Match<Player>::set_result(match_result new_result);
template void Match<Team>::set_result(match_result new_result);
template double Match<Player>::get_participant_result(Player const& participant) const;
template double Match<Team>::get_participant_result(Team const& participant) const;
template void Match<Player>::determine_winner(bool draw_allowed);
template void Match<Team>::determine_winner(bool draw_allowed);
