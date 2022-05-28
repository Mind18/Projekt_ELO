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


vector<Player> player_add(vector<Player> player_vect)
{
    string name = "";
    int elo_points = 0;
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
        Player p1(player_vect[player_vect.size()-1].get_id()+1, name, elo_points);
        player_vect.push_back(p1);
        }
    else
    {
        Player p1(1, name, elo_points);
        player_vect.push_back(p1);
    }
    return player_vect;
}

vector<Team> team_add(vector<Team> team_vect)
{
    string name = "";
    int elo_points = 0;
    vector<Player> player_vect;
    int n_players = 0;
    cout << "Type name of team\n";
    while(!(cin >> name))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "---invalid team name---\n";
    }
    cout << "Type number of players in team\n";
    while(!(cin >> n_players) or n_players < 0 or n_players > 30)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "---invalid team size---\n";
    }
    for(int i=0; i<n_players; i++)
    {
        player_vect = player_add(player_vect);
    }

    cout << "Type elo_points of team\n";
    while(!(cin >> elo_points) or elo_points < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "---invalid elo points---\n";
    }

    if(team_vect.size() > 0)
    {
    Team t1(team_vect[team_vect.size()-1].get_id()+1, name, player_vect, elo_points);
    team_vect.push_back(t1);
    }
    else
    {
        Team t1(1, name, player_vect, elo_points);
        team_vect.push_back(t1);
    }

    return team_vect;
}


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
            player_vect = player_add(player_vect);
            player_vect[player_vect.size()-1].print();
            break;
        }
        else if(league_type_option == 2)
        {
            team_vect = team_add(team_vect);
            team_vect[team_vect.size()-1].print();
            break;
        }
    default:
        break;
    }

    return 0;
}

