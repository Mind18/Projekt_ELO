#include "Match.h"
#include "Player.h"
#include "Team.h"
#include <iostream>

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

template void Match<Player>::set_result(match_result new_result);
template void Match<Team>::set_result(match_result new_result);
template double Match<Player>::get_participant_result(Player const& participant) const;
template double Match<Team>::get_participant_result(Team const& participant) const;
