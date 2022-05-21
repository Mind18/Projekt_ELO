#include "League.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


// template <typename T> T League<T>::get_participant_by_id(unsigned int part_id)
// {
//     for(int i=0; i < Participants.size(); i++)
//     {
//         if(Participants[i].get_id() == part_id)
//         {
//             return Participants[i];
//         }
//     }
//     throw wrong_id;
// };

template <typename T> double League<T>::simulate_match(unsigned int part_id, unsigned int part2_id, unsigned int last_match_id)
{
    Match <T> m1 (last_match_id, part_id, part2_id);
    m1.determine_winner(part_id, part2_id);
    return m1.get_participant_result(part_id);
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
