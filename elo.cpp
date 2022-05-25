#include "Team.h"
#include "League.h"
#include "Match.h"
#include "Player.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

int main()
{
    vector<Team> team_vect;
    vector<Player> player_vect;


    int options[2] = {1, 2};
    int option = 0;
    string file_name = "";
    cout << "Elo programm start\n";
    cout << "Press enter to continue\n";
    cin.get();
    system("clear");
    cout << "Main menu\n" << "choose an option from below:\n";
    cout << "\t(1) load team file\n";
    cout << "\t(2) load player file\n";
    cout << "\t";
    while(!(cin >> option) and option<1 or option>sizeof(options))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "---invalid option, please choose one from above---\n";
    }

    switch (option)
    {
    case 1:
        cout << "Type a path to file:\n";
        while(!(cin >> file_name))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---invalid file name---\n";
        }
        // team_vect = team_read(" ", team_vect, 0);
        break;
    case 2:
        cout << "Type a path to file:\n";
        while(!(cin >> file_name))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---invalid file name---\n";
        }
        player_vect = player_read(file_name, player_vect, 0);
        break;
    default:
        break;
    }

    return 0;
}
