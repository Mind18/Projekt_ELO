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


vector<Player> player_add(vector<Player> player_vect, League<Player>& player_league)
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
        player_league.set_standing_zero(p1);
        }
    else
    {
        Player p1(1, name, elo_points);
        player_vect.push_back(p1);
        player_league.set_standing_zero(p1);
    }
    return player_vect;
}

vector<Team> team_add(vector<Team> team_vect, League<Team>& team_league, League<Player> player_league)
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
        player_vect = player_add(player_vect, player_league);
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
    team_league.set_standing_zero(t1);
    }
    else
    {
        Team t1(1, name, player_vect, elo_points);
        team_vect.push_back(t1);
        team_league.set_standing_zero(t1);
    }

    return team_vect;
}


int main()
{
    vector<Team> team_vect;
    vector<Player> player_vect;
    vector<Match<Player>> player_matches;
    map<Player, double> player_table;
    vector<Match<Team>> team_matches;
    map<Team, double> team_table;
    League<Player> player_league (1, player_vect, player_matches, player_table, 0, 0, 0, 0);
    League<Team> team_league (1, team_vect, team_matches, team_table, 0, 0, 0, 0);

    double win = 0;
    double lose = 0;
    bool is_draw_allowed = 1;
    double draw = 0;

    int league_type_options[2] = {1, 2};
    int add_options[8] = {1, 2, 3, 4, 5, 6, 7, 9};
    int league_type_option = 0;
    int add_option = 0;
    string file_name = "";
    system("clear");
    cout << "Elo programm start\n";
    cout << "Press enter to continue\n";
    cin.get();
    system("clear");
    cout << "Main menu\n" << "Choose an option from below:\n";

    cout << "(1) Player league simulation\n";
    cout << "(2) Team league simulation\n";

    while(!(cin >> league_type_option) or (league_type_option<1 or league_type_option>2))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "---invalid option, please choose one from above---\n";
    }


    cout << "Type number of points scored after win\n";
    while(!(cin >> win))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "---invalid input, please type number---\n";
    }
    cout << "Type number of points scored after lose\n";
    while(!(cin >> lose))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "---invalid input, please type number---\n";
    }
    cout << "Is draw allowed in your League?\n";
    cout << "(0) no\n";
    cout << "(1) yes\n";
    while(!(cin >> is_draw_allowed))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "---invalid option, please choose (0) or (1)---\n";
    }
    if(is_draw_allowed)
    {
        cout << "Type number of points scored after draw\n";
        while(!(cin >> draw))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---invalid input, please type number---\n";
        }
    }
    if(league_type_option == 1)
    {
        player_league.set_draw_allowed(is_draw_allowed);
        player_league.set_pts_draw(draw);
        player_league.set_pts_win(win);
        player_league.set_pts_lose(lose);
    }
    else if(league_type_option == 2)
    {
        team_league.set_draw_allowed(is_draw_allowed);
        team_league.set_pts_draw(draw);
        team_league.set_pts_win(win);
        team_league.set_pts_lose(lose);
    }

    league_menu:
    system("clear");
    if(league_type_option == 1)
    {
        cout << "(1) Load player file\n";
        cout << "(2) Add player\n";
        cout << "(3) Print current players in league\n";
        cout << "(4) Write players to a file\n";
    }
    else if(league_type_option == 2)
    {
        cout << "(1) Load team file\n";
        cout << "(2) Add team\n";
        cout << "(3) Print current teams in league\n";
        cout << "(4) Write teams to a file\n";
    }
    cout << "(5) Simulate whole league\n";
    cout << "(6) Print league standings\n";
    cout << "(7) Monte Carlo analysis\n";
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
    unsigned int rounds = 1;
    unsigned int rounds_monte_carlo = 1;
    unsigned int iterations = 1;

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
            {
                try
                {player_vect = player_read(file_name, player_vect, player_vect[player_vect.size()-1].get_id(), player_league);}
                catch(const std::exception& e)
                    {cout << "Wrong format of file, please make file in a template:\n";
                    cout << "Player Name, [elo_points]\n";}
            }
            else
            {
                try
                {player_vect = player_read(file_name, player_vect, 0, player_league);}
                catch(const std::exception& e)
                    {cout << "Wrong format of file, please make file in a template:\n";
                    cout << "'Player Name', [elo_points]\n";}
            }
            player_league.set_participants(player_vect);
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
            if(team_vect.size() > 0)
            {
                try
                {team_vect = team_read(file_name, team_vect, team_vect[team_vect.size()-1].get_id(), team_league);}
                catch(const std::exception& e)
                    {cout << "Wrong format of file, please make file in a template:\n";
                    cout << "'Team Name': [team_elo_points], 'Player Name', [player_elo_points],...\n";}

            }
            else
            {
                try
                {team_vect = team_read(file_name, team_vect, 0, team_league);}
                catch(const std::exception& e)
                    {cout << "Wrong format of file, please make file in a template:\n";
                    cout << "'Team Name': [team_elo_points], 'Player Name', [player_elo_points],...\n";}
            }
            team_league.set_participants(team_vect);
            break;
        }
    case 2:
        if(league_type_option == 1)
        {
            player_vect = player_add(player_vect, player_league);
            player_league.set_participants(player_vect);
            break;
        }
        else if(league_type_option == 2)
        {
            team_vect = team_add(team_vect, team_league, player_league);
            team_league.set_participants(team_vect);
            break;
        }
    case 3:
        if(league_type_option == 1)
        {
            for(size_t i=0; i<player_vect.size(); i++)
                player_league.get_participants()[i].print();
            break;
        }
        else if(league_type_option == 2)
        {
            for(size_t i=0; i<team_vect.size(); i++)
                team_league.get_participants()[i].print();
            break;
        }
    case 4:
        if(league_type_option == 1)
        {
            cout << "Type name of file where you want to write players\n";
            while(!(cin >> file_name))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "---invalid file name---\n";
            }
            player_write(file_name, player_league.get_participants());
            break;
        }
        else if(league_type_option == 2)
        {
            cout << "Type name of file where you want to write teams\n";
            while(!(cin >> file_name))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "---invalid file name---\n";
            }
            team_write(file_name, team_league.get_participants());
            break;
        }
    case 5:
        cout << "Type number of rematches in this simulation\n";
        while(!(cin >> rounds))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---invalid number---\n";
        }
        cout << '\n';
        if(league_type_option == 1)
        {
            player_league.clear_standings();
            if(player_league.get_participants().size()<2)
            {
                cout << "---First insert more than 1 player in your league then, simulate it---\n";
                break;
            }
            try
            {
                player_league.simulate_league(rounds+1);
            }
            catch(const my_exceptions& invalid_schedule)
            {
                cout << "---First insert players in your league then, simulate it---\n";
            }
            break;
        }
        else if(league_type_option == 2)
        {
            team_league.clear_standings();
            if(team_league.get_participants().size()<2)
            {
                cout << "---First insert more than 1 team in your league then, simulate it---\n";
                break;
            }
            try
            {
                team_league.simulate_league(rounds+1);
            }
            catch(const my_exceptions& invalid_schedule)
            {
                cout << "---First insert teams in your league then, simulate it---\n";
            }
            break;
        }
    case 6:
        if(league_type_option == 1)
        {
            player_league.print_standings();
            break;
        }
        else if(league_type_option == 2)
        {
            team_league.print_standings();
            break;
        }
    case 7:
        cout << "Type number of rematches in this analysis\n";
        while(!(cin >> rounds_monte_carlo))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---invalid number---\n";
        }
        cout << "Type number of times league will be simulated in this analysis\n";
        while(!(cin >> iterations))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "---invalid number---\n";
        }
        cout << '\n';
        if(league_type_option == 1)
        {
            player_league.clear_standings();
            if(player_league.get_participants().size()<2)
            {
                cout << "---First insert more than 1 player in your league then, make Monte Carlo analysis---\n";
                break;
            }
            try
            {
                map<Player, map<int, int>> monte_carlo_player_results = player_league.monte_carlo_simulation(iterations, rounds_monte_carlo+1);
                print_monte_carlo(monte_carlo_player_results, iterations);
            }
            catch(const exception e)
            {
                cout << "---First insert players in your league then, make Monte Carlo analysis---\n";
            }
            break;
        }
        else if(league_type_option == 2)
        {
            team_league.clear_standings();
            if(team_league.get_participants().size()<2)
            {
                cout << "---First insert more than 1 team in your league then, make Monte Carlo analysis---\n";
                break;
            }
            try
            {
                map<Team, map<int, int>> monte_carlo_team_results = team_league.monte_carlo_simulation(iterations, rounds_monte_carlo+1);
                print_monte_carlo(monte_carlo_team_results, iterations);
            }
            catch(const exception e)
            {
                cout << "---First insert teams in your league then, make Monte Carlo analysis---\n";
            }
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

