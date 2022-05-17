#include "Team.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 5000);
    if(5*team1.get_elo() == team2.get_elo())
        cout << "Test case 0 passed\n";
    else
        cout << "Test case 0 error\n";

    cout << "End of tests\n";
    cout << "Example of Team.print()\n";
    team1.print();

    return 0;
}