#include "Team.h"
#include "Match.h"
#include "League.h"
#include "Player.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

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
    //Player tests
    //Test operator < and > 0
    if (not(pl2>pl1) or not(pl2<pl3))
    {
        std::cout << "Test operator < and > case 0 error.\n";
    }

    // Test of recalculate_elo() 0

    pl1.set_elo(1400);
    unsigned int pl1_elo = pl1.get_elo();
    unsigned int pl2_elo = pl2.get_elo();
    pl1.recalculate_elo(pl2_elo, 1);
    pl2.recalculate_elo(pl1_elo, 0);
    if (pl1.get_elo() != 1403 || pl2.get_elo() != 997)
    {
        cout << "Test of Player::recalculate_elo() 0 failed.\nGiven parameters:\n";
        cout << "Player 1 elo before change: " << pl1_elo << "\n";
        cout << "Player 2 elo before change: " << pl2_elo << "\n";
        cout << "Player 1 elo after change: " << pl1.get_elo() << "\n";
        cout << "Player 2 elo after change: " << pl2.get_elo() << "\n";
        cout << '\n';
    }

    // Test of recalculate_elo() 1

    pl1.set_elo(1400);
    pl2.set_elo(1000);
    pl1_elo = pl1.get_elo();
    pl2_elo = pl2.get_elo();
    pl1.recalculate_elo(pl2_elo, 0);
    pl2.recalculate_elo(pl1_elo, 1);
    if (pl1.get_elo() != 1371 || pl2.get_elo() != 1029)
    {
        cout << "Test of Player::recalculate_elo() 1 failed.\nGiven parameters:\n";
        cout << "Player 1 elo before change: " << pl1_elo << "\n";
        cout << "Player 2 elo before change: " << pl2_elo << "\n";
        cout << "Player 1 elo after change: " << pl1.get_elo() << "\n";
        cout << "Player 2 elo after change: " << pl2.get_elo() << "\n";
        cout << '\n';
    }

    // Test of recalculate_elo() 2

    pl1.set_elo(1400);
    pl2.set_elo(1000);
    pl1_elo = pl1.get_elo();
    pl2_elo = pl2.get_elo();
    pl1.recalculate_elo(pl2_elo, 0.5);
    pl2.recalculate_elo(pl1_elo, 0.5);
    if (pl1.get_elo() != 1387 || pl2.get_elo() != 1013)
    {
        cout << "Test of Player::recalculate_elo() 2 failed.\nGiven parameters:\n";
        cout << "Player 1 elo before change: " << pl1_elo << "\n";
        cout << "Player 2 elo before change: " << pl2_elo << "\n";
        cout << "Player 1 elo after change: " << pl1.get_elo() << "\n";
        cout << "Player 2 elo after change: " << pl2.get_elo() << "\n";
        cout << '\n';
    }

    // Test of recalculate_elo() 3

    try
    {
        pl1.set_elo(1400);
        pl1_elo = pl1.get_elo();
        pl2_elo = pl2.get_elo();
        pl1.recalculate_elo(pl2_elo, 1.5);
    }
    catch (Exceptions invalid_result)
    {
        cout << "Test of Player::recalculate_elo() 3 passed.\n";
    }

    // Test of recalculate_elo() 4

    try
    {
        pl1.set_elo(1400);
        pl1_elo = pl1.get_elo();
        pl2_elo = pl2.get_elo();
        pl2.recalculate_elo(pl2_elo, -0.5);
    }
    catch (Exceptions invalid_result)
    {
        cout << "Test of Player::recalculate_elo() 4 passed.\n";
    }

    //Test player_read() 0

    vector<Player> player_vect;
    std::string file = "test_player_read.txt";
    player_vect = player_read(file, player_vect, 0);
    if(player_vect.size() != 5)
    {
        std::cout << "Test player_read() case 0 error.\n Size given: 5\n";
        std::cout << "Size after read: " << player_vect.size() << std::endl;
    }
    // cout << endl << player_vect.size() << endl;

    //Team tests

    cout << "Beggining of Team tests:\n";

    // Test get_elo() 0

    if (5*team1.get_elo() != team2.get_elo())
    {
        cout << "Test get_elo() case 0 error. Values given: \n";
        cout << "Team 1 times 5: " << 5 * team1.get_elo() << '\n';
        cout << "Team 2: " << team2.get_elo() << '\n';
    }

    //Test get_elo() 1

    team2.set_elo(1100);
    if (team1.get_elo() + 100 != team2.get_elo())
    {
        cout << "Test get_elo() case 1 error. Values given: \n";
        cout << "Team 1 plus 100: " << team1.get_elo() + 100 << '\n';
        cout << "Team 2: " << team2.get_elo() << '\n';
    }

    //Test of remove_member() 0
    team1.remove_member(2);
    if(team1.get_n_members() != 2)
    {
        cout << "Test remove_member() case 0 error. Size: ";
        cout << team1.get_n_members() << endl;
        team1.print();
    }
    //Test of operator==() 0

    Team team3(1, "Na pewno nie Legia", play_vect);
    if (team1 != team3)
    {
        cout << "Test operator==() case 0 error. Teams id: ";
        cout << "Team 1: " << team1.get_id() << '\n';
        cout << "Team 2: " << team3.get_id() << '\n';
    }

    // Test of recalculate_elo() 0

    team1.set_elo(1800);
    team2.set_elo(2050);
    unsigned int team1_elo = team1.get_elo();
    unsigned int team2_elo = team2.get_elo();
    team1.recalculate_elo(team2_elo, 1);
    team2.recalculate_elo(team1_elo, 0);
    if (team1.get_elo() != 1826 || team2.get_elo() != 2024)
    {
        cout << "Test of Team::recalculate_elo() 0 failed.\nGiven parameters:\n";
        cout << "Team 1 elo before change: " << team1_elo << "\n";
        cout << "Team 2 elo before change: " << team2_elo << "\n";
        cout << "Team 1 elo after change: " << team1.get_elo() << "\n";
        cout << "Team 2 elo after change: " << team2.get_elo() << "\n";
        cout << '\n';
    }

    // Test of recalculate_elo() 1

    team1.set_elo(1800);
    team2.set_elo(2050);
    team1_elo = team1.get_elo();
    team2_elo = team2.get_elo();
    team1.recalculate_elo(team2_elo, 0);
    team2.recalculate_elo(team1_elo, 1);
    if (team1.get_elo() != 1794 || team2.get_elo() != 2056)
    {
        cout << "Test of Team::recalculate_elo() 0 failed.\nGiven parameters:\n";
        cout << "Team 1 elo before change: " << team1_elo << "\n";
        cout << "Team 2 elo before change: " << team2_elo << "\n";
        cout << "Team 1 elo after change: " << team1.get_elo() << "\n";
        cout << "Team 2 elo after change: " << team2.get_elo() << "\n";
        cout << '\n';
    }

    // Test of recalculate_elo() 2

    team1.set_elo(1800);
    team2.set_elo(2050);
    team1_elo = team1.get_elo();
    team2_elo = team2.get_elo();
    team1.recalculate_elo(team2_elo, 0.5);
    team2.recalculate_elo(team1_elo, 0.5);
    if (team1.get_elo() != 1810 || team2.get_elo() != 2040)
    {
        cout << "Test of Team::recalculate_elo() 0 failed.\nGiven parameters:\n";
        cout << "Team 1 elo before change: " << team1_elo << "\n";
        cout << "Team 2 elo before change: " << team2_elo << "\n";
        cout << "Team 1 elo after change: " << team1.get_elo() << "\n";
        cout << "Team 2 elo after change: " << team2.get_elo() << "\n";
        cout << '\n';
    }

    // Test of recalculate_elo() 3

    try
    {
        team1.set_elo(800);
        team1_elo = team1.get_elo();
        team2_elo = team2.get_elo();
        team1.recalculate_elo(team2_elo, 3.02);
    }
    catch (Exceptions invalid_result)
    {
        cout << "Test of Team::recalculate_elo() 3 passed.\n";
    }

    // Test of recalculate_elo() 4

    try
    {
        team1.set_elo(720);
        team1_elo = team1.get_elo();
        team2_elo = team2.get_elo();
        team2.recalculate_elo(team2_elo, -0.332);
    }
    catch (Exceptions invalid_result)
    {
        cout << "Test of Team::recalculate_elo() 4 passed.\n";
    }

    //Match tests
    cout << "Tests of Match:\n";
    //Test of operator==() 0
    Match<Team> m1(1, team1, team2);
    Match<Team> m2(2, team1, team2);
    if(m1 == m2 or m1 != m1)
    {
        cout << "Test operator==() case 0 error. Matches id:\n";
        cout << "Match 1: " << m1.get_id() << '\n';
        cout << "Match 2: " << m2.get_id() << '\n';
    }

    //Test of get_participant_result() 0
    m1.set_result(Participant1);
    if (m1.get_participant_result(team1) != 1.0)
    {
        cout << "Test get_participant_result() case 0 error. Result given: " << '\n';
        cout << m1.get_participant_result(team1) << '\n';
    }

    //Test of get_participant_result() 1
    try
    {
        m2.get_participant_result(team2);
    }
    catch (my_exceptions illegal_result)
    {
        cout << "Test get_participant_result() case 1 passed." << '\n';
    }

    //Test of get_participant_result() 2
    try
    {
        m2.get_participant_result(team3);
    }
    catch (my_exceptions invalid_participant)
    {
        cout << "Test get_participant_result() case 2 passed." << '\n';
    }

    //Test of get_participant_result() 3
    m2.set_result(Draw);
    if (m2.get_participant_result(team2) != 0.5)
    {
        cout << "Test get_participant_result() case 3 error. Result given: " << '\n';
        cout << m2.get_participant_result(team2) << '\n';
    }

    //League tests
    {
    //Test case 0
        Player pl1 (1, "jedrzejczyk");
        Player pl2 (2, "lewandowski");
        Player pl3 (3, "blaszczykowski");
        Match <Player> m1 (1, pl1, pl2);
        Match <Player> m2 (2, pl2, pl3);
        std::vector<Player> play_vect {pl1, pl2, pl3};
        vector<Match <Player>> matches {m1, m2};
        std::map<Player, double> standings;
        standings[pl1] = 4;
        standings[pl2] = 3;
        standings[pl3] = 1;
        League <Player> l1(1, play_vect, matches, standings, 3, 1, 100, 0);
        if(l1.get_pts_draw()!=0)
            std::cout << "Error League test case 0";

    //Test case 0 get_participant_by_id()
        if(l1.get_participant_by_id(3) != pl3)
            std::cout << "Error League get_participant_by_id() test case 0\n";

        // l1.print_standings();
    }
    std::cout << "End of tests\n";

    return 0;
}