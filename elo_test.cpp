#include "Team.h"
#include <string>
#include <fstream>
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

    cout << "Beggining of tests.\n";

    // Test get_elo() 0

    if (5*team1.get_elo() != team2.get_elo())
    {
        cout << "Test get_elo() case 0 error. Values given: \n";
        cout << "Team 1 times 5: " << 5 * team1.get_elo() << '\n';
        cout << "Team 2: " << team2.get_elo() << '\n';
    }
    else cout << "Test get_elo() 0 passed\n";

    //Test get_elo() 1

    team2.set_elo(1100);
    if (team1.get_elo() + 100 != team2.get_elo())
    {
        cout << "Test get_elo() case 1 error. Values given: \n";
        cout << "Team 1 plus 100: " << team1.get_elo() + 100 << '\n';
        cout << "Team 2: " << team2.get_elo() << '\n';
    }
    else cout << "Test get_elo() 1 passed\n";

    //Test player_read() 0

    vector<Player> player_vect;
    string file = "test_player_read.txt";
    player_read(file, player_vect, 0);
    cout << player_vect.size() << endl;
    cout << '\n';
    player_vect[0].print();

    //Test of operator==() 0

    Team team3(1, "Na pewno nie Legia", play_vect);
    if (team1 != team3)
    {
        cout << "Test operator==() case 0 error. Teams id: ";
        cout << "Team 1: " << team1.get_id() << '\n';
        cout << "Team 2: " << team3.get_id() << '\n';
    }

    cout << "End of tests\n";
    cout << "Example of Team.print()\n";
    team1.print();

    return 0;
}