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
    while(!getline(cin >> ws, name))
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
    while(!getline(cin >> ws, name))
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
    double win = 0;
    double lose = 0;
    bool is_draw_allowed = 1;
    double draw = 0;

    int league_type_options[2] = {1, 2};
    int add_options[4] = {1, 2, 3, 9};
    int league_type_option = 0;
    int add_option = 0;
    string file_name = "";
    cout << "Elo programm start\n";
    cout << "Press enter to continue\n";
    cin.get();
    system("clear");
    cout << "Main menu\n" << "Choose an option from below:\n";

    cout << "(1) Player league simulation\n";
    cout << "(2) Team league simulation\n";

    while(!(cin >> league_type_option) and league_type_option<1
    or league_type_option>sizeof(league_type_options))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "---invalid option, please choose one from above---\n";
    }

    if(league_type_option == 1)
    {
        vector<Match<Player>> matches;
        map<Player, double> table;

        cout << "Type value of points that player recieves after win\n";
        while(!(cin >> win))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---invalid input, please type number---\n";
        }
        cout << "Type value of points that player recieves after lose\n";
        while(!(cin >> lose))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---invalid input, please type number---\n";
        }
        cout << "Is draw allowed in your League?\n";
        cout << "(1) yes\n";
        cout << "(0) no\n";
        while(!(cin >> is_draw_allowed))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---invalid option, please choose (1) or (2)---\n";
        }
        if(is_draw_allowed)
        {
            cout << "Type value of points that player recieves after draw\n";
            while(!(cin >> draw))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "---invalid input, please type number---\n";
            }
        }

        League<Player> player_league (1, player_vect, matches, table, win, draw, lose, is_draw_allowed);
    }

    league_menu:
    system("clear");
    if(league_type_option == 1)
    {
        cout << "(1) Load player file\n";
        cout << "(2) Add player\n";
        cout << "(3) Print current players in league\n";
    }
    else if(league_type_option == 2)
    {
        cout << "(1) Load team file\n";
        cout << "(2) Add team\n";
        cout << "(3) Print current teams in league\n";
    }
    cout << "(9) Quit\n";

    while(!(cin >> add_option) or add_option<1 or add_option>sizeof(add_options))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "---invalid option, please choose one from above---\n";
    }
    system("clear");

    if(add_option == 9) return 0;

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
            if(player_vect.size()>0)
                try
                {player_vect = player_read(file_name, player_vect, player_vect[player_vect.size()-1].get_id());}
                catch(const std::exception& e)
                    {cout << "Wrong format of file, please make file in a template:\n";
                    cout << "Player Name, [elo_points]\n";}
            else
                try
                {player_vect = player_read(file_name, player_vect, 0);}
                catch(const std::exception& e)
                    {cout << "Wrong format of file, please make file in a template:\n";
                    cout << "'Player Name', [elo_points]\n";}
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
            try
            {team_vect = team_read(file_name, team_vect, 0);}
            catch(const std::exception& e)
                {cout << "Wrong format of file, please make file in a template:\n";
                cout << "'Team Name': [team_elo_points], 'Player Name', [player_elo_points],...\n";}
            break;
        }
    case 2:
        if(league_type_option == 1)
        {
            player_vect = player_add(player_vect);
            break;
        }
        else if(league_type_option == 2)
        {
            team_vect = team_add(team_vect);
            break;
        }
    case 3:
        if(league_type_option == 1)
        {
            for(size_t i=0; i<player_vect.size(); i++)
                player_vect[i].print();
            break;
        }
        else if(league_type_option == 2)
        {
            for(size_t i=0; i<team_vect.size(); i++)
                team_vect[i].print();
            break;
        }
    default:
        break;
    }
    cout << "\nPress enter and go back to menu\n";
    cin.get();
    cin.get();
    goto league_menu;

    return 0;
}

