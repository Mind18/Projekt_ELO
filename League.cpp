#include "League.h"

#include <iostream>
#include <map>
#include <vector>
#include <fstream>

using namespace std;


template <typename T> void League<T>::print_standings()
{
    typename std::map<T, double>::iterator it = standings.begin();
    while (it != standings.end())
    {
        std::cout << "Participant: " << it->first.get_name() << " points: " << it->second << std::endl;
        it++;
    }
}
