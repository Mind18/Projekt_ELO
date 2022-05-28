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
    int league_type_option = 0;
    int add_option = 0;
    string file_name = "";
    cout << "Elo programm start\n";
    cout << "Press enter to continue\n";
    cin.get();
    system("clear");
    cout << "Main menu\n" << "choose an option from below:\n";

    cout << "\t(1) player league simulation\n";
    cout << "\t(2) team league simulation\n";
    while(!(cin >> league_type_option) and league_type_option<1
    or league_type_option>sizeof(options))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "---invalid option, please choose one from above---\n";
    }
    system("clear");

    if(league_type_option == 1)
    {
        cout << "\t(1) load player file\n";
        cout << "\t(2) add player\n";
        cout << "\t";
    }
    else if(league_type_option == 2)
    {
        cout << "\t(1) load team file\n";
        cout << "\t(2) add team\n";
        cout << "\t";
    }

    while(!(cin >> add_option) and add_option<1 or add_option>sizeof(options))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "---invalid option, please choose one from above---\n";
    }
    system("clear");


    string name = "";
    int elo_points = 0;
    switch (add_option)
    {
    case 1:
        cout << "Type a path to file:\n";
        if(league_type_option==1)
        {
            while(!(cin >> file_name))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "---invalid file name---\n";
            }
            player_vect = player_read(file_name, player_vect, 0);
            break;
        }
        else if(league_type_option==2)
        {
            while(!(cin >> file_name))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "---invalid file name---\n";
            }
            // team_vect = team_read(" ", team_vect, 0);
            break;
        }
    case 2:
        if(league_type_option == 1)
        {
            cout << "Type name of player\n";
            while(!(cin >> name))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "---invalid player name---\n";
            }
            cout << "Type elo_points of player\n";
            while(!(cin >> elo_points) or elo_points < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "---invalid elo points---\n";
            }
            if(player_vect.size() > 0)
                {
                Player p1(player_vect[player_vect.size()].get_id()+1, name, elo_points);
                player_vect.push_back(p1);
                }
            else
            {
                Player p1(1, name, elo_points);
                player_vect.push_back(p1);
            }
            break;
        }
        else if(league_type_option == 2)
        {
            cout << "Type name of team\n";
            while(!(cin >> name))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "---invalid player name---\n";
            }
            break;
        }
    default:
        break;
    }

    return 0;
}
