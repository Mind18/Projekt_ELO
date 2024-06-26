#include "../Team.h"
#include "../Match.h"
#include "../League.h"
#include "../Player.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <catch2/catch.hpp>

using namespace std;

TEST_CASE("Classes constructors and getters", "[coordinates]")
{
    CHECK(true);
}

TEST_CASE("Test of operator < and > 0", "[Player class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 5000);
    CHECK(pl2>pl1);
    CHECK(pl2<pl3);
}

TEST_CASE("Test of recalculate_elo() 0", "[Player class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    pl1.set_elo(1400);
    unsigned int pl1_elo = pl1.get_elo();
    unsigned int pl2_elo = pl2.get_elo();
    pl1.recalculate_elo(pl2_elo, 1);
    pl2.recalculate_elo(pl1_elo, 0);
    CHECK(pl1.get_elo() == 1403);
    CHECK(pl2.get_elo() == 997);
}

TEST_CASE("Test of recalculate_elo() 1", "[Player class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    pl1.set_elo(1400);
    pl2.set_elo(1000);
    unsigned int pl1_elo = pl1.get_elo();
    unsigned int pl2_elo = pl2.get_elo();
    pl1.recalculate_elo(pl2_elo, 0);
    pl2.recalculate_elo(pl1_elo, 1);
    CHECK(pl1.get_elo() == 1371);
    CHECK(pl2.get_elo() == 1029);
}

TEST_CASE("Test of recalculate_elo() 2", "[Player class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    pl1.set_elo(1400);
    pl2.set_elo(1000);
    unsigned int pl1_elo = pl1.get_elo();
    unsigned int pl2_elo = pl2.get_elo();
    pl1.recalculate_elo(pl2_elo, 0.5);
    pl2.recalculate_elo(pl1_elo, 0.5);
    CHECK(pl1.get_elo() == 1387);
    CHECK(pl2.get_elo() == 1013);
}

TEST_CASE("Test of recalculate_elo() 3", "[Player class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    pl1.set_elo(1400);
    unsigned int pl1_elo = pl1.get_elo();
    unsigned int pl2_elo = pl2.get_elo();
    CHECK_THROWS_AS(pl1.recalculate_elo(pl2_elo, 1.5), my_exceptions);
}

TEST_CASE("Test of recalculate_elo() 4", "[Player class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    pl1.set_elo(1400);
    unsigned int pl1_elo = pl1.get_elo();
    unsigned int pl2_elo = pl2.get_elo();
    CHECK_THROWS_AS(pl1.recalculate_elo(pl2_elo, -0.5), my_exceptions);
}

TEST_CASE("Test of player_read() 0", "[Player class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 5000);
    vector<Player> player_vect;
    std::string file = "test_player_read.txt";
    vector<Match<Player>> matches;
    map<Player, double> table;
    League<Player> player_league(1, play_vect, matches, table, 0,0,0,0);;
    player_vect = player_read(file, player_vect, 0, player_league);
    CHECK(player_vect.size() == 5);
}

// Team tests

TEST_CASE("Test of get_elo() 0", "[Team class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 5000);
    CHECK(5*team1.get_elo() == team2.get_elo());
}

TEST_CASE("Test of get_elo() 1", "[Team class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 5000);
    team2.set_elo(1100);
    CHECK(team1.get_elo() + 100 == team2.get_elo());
}

TEST_CASE("Test of remove_member() 0", "[Team class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    team1.remove_member(2);
    CHECK(team1.get_n_members() == 2);
}

TEST_CASE("Test of operator==() 0", "[Team class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    Team team3(1, "Na pewno nie Legia", play_vect);
    CHECK(team1 == team3);
}

TEST_CASE("Test recalculate_elo() 0", "[Team class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    team1.set_elo(1800);
    team2.set_elo(2050);
    unsigned int team1_elo = team1.get_elo();
    unsigned int team2_elo = team2.get_elo();
    team1.recalculate_elo(team2_elo, 1);
    team2.recalculate_elo(team1_elo, 0);
    REQUIRE(team1.get_elo() == 1826);
    REQUIRE(team2.get_elo() == 2024);
}

TEST_CASE("Test recalculate_elo() 1", "[Team class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    team1.set_elo(1800);
    team2.set_elo(2050);
    unsigned int team1_elo = team1.get_elo();
    unsigned int team2_elo = team2.get_elo();
    team1.recalculate_elo(team2_elo, 0);
    team2.recalculate_elo(team1_elo, 1);
    REQUIRE(team1.get_elo() == 1794);
    REQUIRE(team2.get_elo() == 2056);
}

TEST_CASE("Test recalculate_elo() 2", "[Team class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    team1.set_elo(1800);
    team2.set_elo(2050);
    unsigned int team1_elo = team1.get_elo();
    unsigned int team2_elo = team2.get_elo();
    team1.recalculate_elo(team2_elo, 0.5);
    team2.recalculate_elo(team1_elo, 0.5);
    REQUIRE(team1.get_elo() == 1810);
    REQUIRE(team2.get_elo() == 2040);
}

TEST_CASE("Test recalculate_elo() 3", "[Team class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    team1.set_elo(1800);
    team2.set_elo(2050);
    unsigned int team1_elo = team1.get_elo();
    unsigned int team2_elo = team2.get_elo();
    team1.recalculate_elo(team2_elo, 0.5);
    team2.recalculate_elo(team1_elo, 0.5);
    REQUIRE(team1.get_elo() == 1810);
    REQUIRE(team2.get_elo() == 2040);
}

TEST_CASE("Test recalculate_elo() 4", "[Team class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    team1.set_elo(800);
    team2.set_elo(2050);
    unsigned int team1_elo = team1.get_elo();
    unsigned int team2_elo = team2.get_elo();
    CHECK_THROWS_AS(team1.recalculate_elo(team1_elo, 3.02), my_exceptions);
}

TEST_CASE("Test recalculate_elo() 5", "[Team class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    team1.set_elo(720);
    team2.set_elo(2050);
    unsigned int team1_elo = team1.get_elo();
    unsigned int team2_elo = team2.get_elo();
    CHECK_THROWS_AS(team1.recalculate_elo(team1_elo, -0.332), my_exceptions);
}

TEST_CASE("Test of team_read() 0", "[Team calss]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    vector<Team> team_vect;
    vector<Match<Team>> matches;
    map<Team, double> table;
    League<Team> team_league(1, team_vect, matches, table, 0,0,0,0);
    std::string file = "test_team_read.txt";
    team_vect = team_read(file, team_vect, 0, team_league);
    CHECK(team_vect.size() == 6);
}

// Match tests

TEST_CASE("Test of match.operator==() 0", "[Match class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    Match<Team> m1(1, team1, team2);
    Match<Team> m2(2, team1, team2);
    CHECK(m1 != m2);
    CHECK(m1 == m1);
}

TEST_CASE("Test of get_participant_result() 0", "[Match class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    Match<Team> m1(1, team1, team2);
    Match<Team> m2(2, team1, team2);
    m1.set_result(Participant1);
    CHECK(m1.get_participant_result(team1) == 1.0);
}

TEST_CASE("Test of get_participant_result() 1", "[Match class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    Match<Team> m1(1, team1, team2);
    Match<Team> m2(2, team1, team2);
    m1.set_result(Participant1);
    CHECK_THROWS_AS(m2.get_participant_result(team2), my_exceptions);
}

TEST_CASE("Test of get_participant_result() 2", "[Match class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    Team team3(1, "Na pewno nie Legia", play_vect);
    Match<Team> m1(1, team1, team2);
    Match<Team> m2(2, team1, team2);
    m1.set_result(Participant1);
    CHECK_THROWS_AS(m2.get_participant_result(team3), my_exceptions);
}

TEST_CASE("Test of get_participant_result() 3", "[Match class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    Match<Team> m1(1, team1, team2);
    Match<Team> m2(2, team1, team2);
    m1.set_result(Participant1);
    m2.set_result(Draw);
    CHECK(m2.get_participant_result(team2) == 0.5);
}

TEST_CASE("Test of determine_winner() 0", "[Match class]")
{
    Player pl1 (1, "jedrzejczyk", 800);
    Player pl2 (2, "lewandowski", 1400);
    Match<Player> m1(1, pl1, pl2);
    m1.determine_winner(false);
    std::cout << m1.get_result() << '\n';
    CHECK(m1.get_result() == Participant2);
}

TEST_CASE("Test of determine_winner() 1", "[Match class]")
{
    Player pl1 (1, "jedrzejczyk");
    Player pl2 (2, "lewandowski");
    Player pl3 (3, "blaszczykowski");
    std::vector<Player> play_vect {pl1, pl2, pl3};
    Team team1(1, "Legia", play_vect);
    Team team2(2, "Wisla", play_vect, 1100);
    Match<Team> m1(1, team1, team2);
    m1.determine_winner(false);
    std::cout << m1.get_result() << '\n';
    CHECK(m1.get_result() == Participant1);
}

// League tests

TEST_CASE("Test case 0", "[League tests]")
{
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
    // l1.simulate_match(1, 2, 0);
    CHECK(l1.get_pts_draw() == 0);
}

TEST_CASE("Test of get_participant_by_id() 0", "[League tests]")
{
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
    CHECK(l1.get_participant_by_id(3) == pl3);
}

TEST_CASE("Test of create_schedule() 0", "[League tests]")
{
    Player g2_top(1, "BrokenBlade", 1000);
    Player g2_jng(2, "Jankos", 1000);
    Player g2_mid(3, "caPs", 1000);
    Player g2_adc(4, "Flakked", 1000);
    Player g2_sup(5, "Targamas", 1000);

    Player rng_top(1, "Bin", 1000);
    Player rng_jng(2, "Wei", 1000);
    Player rng_mid(3, "Xiaohu", 1000);
    Player rng_adc(4, "GALA", 1000);
    Player rng_sup(5, "Ming", 1000);

    Player t1_top(1, "Zeus", 1000);
    Player t1_jng(2, "Oner", 1000);
    Player t1_mid(3, "Faker", 1000);
    Player t1_adc(4, "Gumayusi", 1000);
    Player t1_sup(5, "Keria", 1000);

    Player eg_top(1, "Impact", 1000);
    Player eg_jng(2, "Inspired", 1000);
    Player eg_mid(3, "jojopyun", 1000);
    Player eg_adc(4, "Danny", 1000);
    Player eg_sup(5, "Vulcan", 1000);

    vector<Player> g2_players {g2_top, g2_jng, g2_mid, g2_adc, g2_sup};
    vector<Player> rng_players {rng_top, rng_jng, rng_mid, rng_adc, rng_sup};
    vector<Player> t1_players {t1_top, t1_jng, t1_mid, t1_adc, t1_sup};
    vector<Player> eg_players {eg_top, eg_jng, eg_mid, eg_adc, eg_sup};
    Team t1(1, "G2 Esports", g2_players, 1000);
    Team t2(2, "Royal Never Give Up", rng_players, 1200);
    Team t3(3, "T1", t1_players, 1100);
    Team t4(4, "Evil Geniuses", eg_players, 900);
    vector<Match<Team>> schedule;
    map<Team, double> table;
    vector<Team> participants2 {t1, t2, t3, t4};
    League<Team> l2(2, participants2, schedule, table, 3.0, 1.0, 0.0, false);
    Match<Team> exp_match_1(1, t1, t4);
    Match<Team> exp_match_2(2, t2, t3);
    Match<Team> exp_match_3(3, t1, t3);
    Match<Team> exp_match_4(4, t4, t2);
    Match<Team> exp_match_5(5, t1, t2);
    Match<Team> exp_match_6(6, t3, t4);
    vector<Match<Team>> expected_schedule = {exp_match_1, exp_match_2, exp_match_3, exp_match_4, exp_match_5, exp_match_6};
    l2.create_schedule();
    vector<Match<Team>> tested_schedule = l2.get_match_schedule();
    REQUIRE(tested_schedule.size() == expected_schedule.size());
    for(size_t idx = 0; idx < tested_schedule.size(); idx++)
    {
        REQUIRE(tested_schedule[idx] == expected_schedule[idx]);
    }
}

TEST_CASE("Test of create_schedule() 1", "[League tests]")
{
    Player p1(1, "Kacper Radzikowski", 800);
    Player p2(2, "Patryk Płoski", 1000);
    Player p3(3, "Dawid Karbo", 1200);
    Player p4(4, "Adam Bartek", 1000);
    Player p5(5, "Michał Marcin", 900);
    vector<Match<Player>> schedule;
    map<Player, double> table;
    vector<Player> participants3 {p1, p2, p3, p4, p5};
    League<Player> l3(3, participants3, schedule, table, 3.0, 1.0, 0.0, false);
    Match<Player> exp_match_1(1, p1, p4);
    Match<Player> exp_match_2(2, p2, p3);
    Match<Player> exp_match_3(3, p5, p3);
    Match<Player> exp_match_4(4, p1, p2);
    Match<Player> exp_match_5(5, p4, p2);
    Match<Player> exp_match_6(6, p5, p1);
    Match<Player> exp_match_7(7, p3, p1);
    Match<Player> exp_match_8(8, p4, p5);
    Match<Player> exp_match_9(9, p2, p5);
    Match<Player> exp_match_10(10, p3, p4);
    vector<Match<Player>> expected_schedule = {exp_match_1, exp_match_2, exp_match_3,
        exp_match_4, exp_match_5, exp_match_6, exp_match_7, exp_match_8, exp_match_9, exp_match_10};
    l3.create_schedule();
    vector<Match<Player>> tested_schedule = l3.get_match_schedule();
    REQUIRE(tested_schedule.size() == expected_schedule.size());
    for(size_t idx = 0; idx < tested_schedule.size(); idx++)
    {
        std::cout << "Participant 1: " << tested_schedule[idx].get_participant_1().get_name() << " Participant 2: " << tested_schedule[idx].get_participant_2().get_name() << '\n';
        std::cout << "Expected participant 1: " << expected_schedule[idx].get_participant_1().get_name() << " Expected participant 2: " << expected_schedule[idx].get_participant_2().get_name() << '\n';
        REQUIRE(tested_schedule[idx] == expected_schedule[idx]);
    }
}

TEST_CASE("Test of create_schedule() 2", "[League tests]")
{
    Player p1(1, "Kacper Radzikowski", 800);
    Player p2(2, "Patryk Płoski", 1000);
    Player p3(3, "Dawid Karbo", 1200);
    vector<Match<Player>> schedule;
    map<Player, double> table;
    vector<Player> participants3 {p1, p2, p3};
    League<Player> l4(3, participants3, schedule, table, 3.0, 1.0, 0.0, false);
    Match<Player> exp_match_1(1, p1, p2);
    Match<Player> exp_match_2(2, p3, p1);
    Match<Player> exp_match_3(3, p2, p3);
    vector<Match<Player>> expected_schedule = {exp_match_1, exp_match_2, exp_match_3};
    l4.create_schedule();
    vector<Match<Player>> tested_schedule = l4.get_match_schedule();
    REQUIRE(tested_schedule.size() == expected_schedule.size());
    // for(size_t idx = 0; idx < tested_schedule.size(); idx++)
    // {
    //     std::cout << "Participant 1: " << tested_schedule[idx].get_participant_1().get_name() << " Participant 2: " << tested_schedule[idx].get_participant_2().get_name() << '\n';
    //     std::cout << "Expected participant 1: " << expected_schedule[idx].get_participant_1().get_name() << " Expected participant 2: " << expected_schedule[idx].get_participant_2().get_name() << '\n';
    //     REQUIRE(tested_schedule[idx] == expected_schedule[idx]);
    // }
}

TEST_CASE("Test of simulate_match () 0", "[League tests]")
{
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
    match_result result_1 = l1.simulate_match(m2);
    match_result result_2 = m2.get_result();
    REQUIRE(result_1 == result_2);
}

TEST_CASE("Test of simulate_league()", "[League tests]")
{
    Player JSW_1(1, "Stephen Boyer", 1000);
    Player JSW_2(2, "Łukasz Wiśniewski", 1000);
    Player JSW_3(3, "Tomasz Fornal", 1000);
    Player JSW_4(4, "Benjamin Toniutti", 1000);
    Player JSW_5(5, "Jakub Macyra", 1000);
    Player JSW_6(6, "Trevor Clevenot", 1000);

    Player zaksa_1(1, "Marcin Janusz", 1000);
    Player zaksa_2(2, "Norbert Huber", 1000);
    Player zaksa_3(3, "Kamil Semeniuk", 1000);
    Player zaksa_4(4, "Łukasz Kaczmarek", 1000);
    Player zaksa_5(5, "David Smith", 1000);
    Player zaksa_6(6, "Aleksander Śliwka", 1000);

    Player perugia_1(1, "Stefano Mengozzi", 1000);
    Player perugia_2(2, "John Matthew Anderson", 1000);
    Player perugia_3(3, "Wilfredo Leon", 1000);
    Player perugia_4(4, "Oleh Plotnytskyi", 1000);
    Player perugia_5(5, "Simone Giannelli", 1000);
    Player perugia_6(6, "Kamil Rychlicki", 1000);

    Player trentino_1(1, "Alessandro Michieletto", 1000);
    Player trentino_2(2, "Riccardo Sbertoli", 1000);
    Player trentino_3(3, "Marko Podrascanin", 1000);
    Player trentino_4(4, "Matey Kaziyski", 1000);
    Player trentino_5(5, "Daniele Lavia", 1000);
    Player trentino_6(6, "Srecko Lisiniac", 1000);

    vector<Player> JSW_players {JSW_1, JSW_2, JSW_3, JSW_4, JSW_5, JSW_6};
    vector<Player> zaksa_players {zaksa_1, zaksa_2, zaksa_3, zaksa_4, zaksa_5, zaksa_6};
    vector<Player> perugia_players {perugia_1, perugia_2, perugia_3, perugia_4, perugia_5, perugia_6};
    vector<Player> trentino_players {trentino_1, trentino_2, trentino_3, trentino_4, trentino_5, trentino_6};
    Team t1(1, "Jastrzebski Wegiel", JSW_players, 1000);
    Team t2(2, "Zaksa Kedzierzyn-Kozle", zaksa_players, 1200);
    Team t3(3, "Perugia", perugia_players, 1100);
    Team t4(4, "Trentino Itas", trentino_players, 900);
    vector<Match<Team>> schedule;
    map<Team, double> table;
    vector<Team> participants {t1, t2, t3, t4};
    League<Team> l2(2, participants, schedule, table, 3.0, 1.0, 0.0, false);
    l2.create_schedule();
    l2.simulate_league(1);
    map<Team, double> league_standings = l2.get_standings();
    int points_awarded = 0;
    for(auto it = league_standings.begin(); it != league_standings.end(); it++)
    {
        points_awarded += it->second;
    }
    REQUIRE(points_awarded == 18);
}

TEST_CASE("Test of clear_standings()", "[League tests]")
{
    Player JSW_1(1, "Stephen Boyer", 1000);
    Player JSW_2(2, "Łukasz Wiśniewski", 1000);
    Player JSW_3(3, "Tomasz Fornal", 1000);
    Player JSW_4(4, "Benjamin Toniutti", 1000);
    Player JSW_5(5, "Jakub Macyra", 1000);
    Player JSW_6(6, "Trevor Clevenot", 1000);

    Player zaksa_1(1, "Marcin Janusz", 1000);
    Player zaksa_2(2, "Norbert Huber", 1000);
    Player zaksa_3(3, "Kamil Semeniuk", 1000);
    Player zaksa_4(4, "Łukasz Kaczmarek", 1000);
    Player zaksa_5(5, "David Smith", 1000);
    Player zaksa_6(6, "Aleksander Śliwka", 1000);

    Player perugia_1(1, "Stefano Mengozzi", 1000);
    Player perugia_2(2, "John Matthew Anderson", 1000);
    Player perugia_3(3, "Wilfredo Leon", 1000);
    Player perugia_4(4, "Oleh Plotnytskyi", 1000);
    Player perugia_5(5, "Simone Giannelli", 1000);
    Player perugia_6(6, "Kamil Rychlicki", 1000);

    Player trentino_1(1, "Alessandro Michieletto", 1000);
    Player trentino_2(2, "Riccardo Sbertoli", 1000);
    Player trentino_3(3, "Marko Podrascanin", 1000);
    Player trentino_4(4, "Matey Kaziyski", 1000);
    Player trentino_5(5, "Daniele Lavia", 1000);
    Player trentino_6(6, "Srecko Lisiniac", 1000);

    vector<Player> JSW_players {JSW_1, JSW_2, JSW_3, JSW_4, JSW_5, JSW_6};
    vector<Player> zaksa_players {zaksa_1, zaksa_2, zaksa_3, zaksa_4, zaksa_5, zaksa_6};
    vector<Player> perugia_players {perugia_1, perugia_2, perugia_3, perugia_4, perugia_5, perugia_6};
    vector<Player> trentino_players {trentino_1, trentino_2, trentino_3, trentino_4, trentino_5, trentino_6};
    Team t1(1, "Jastrzebski Wegiel", JSW_players, 1000);
    Team t2(2, "Zaksa Kedzierzyn-Kozle", zaksa_players, 1200);
    Team t3(3, "Perugia", perugia_players, 1100);
    Team t4(4, "Trentino Itas", trentino_players, 900);
    vector<Match<Team>> schedule;
    map<Team, double> table;
    vector<Team> participants {t1, t2, t3, t4};
    League<Team> l2(2, participants, schedule, table, 3.0, 1.0, 0.0, false);
    l2.create_schedule();
    l2.simulate_league(1);
    map<Team, double> league_standings = l2.get_standings();
    int points_awarded = 0;
    for(auto it = league_standings.begin(); it != league_standings.end(); it++)
    {
        points_awarded += it->second;
    }
    REQUIRE(points_awarded == 18);
    l2.clear_standings();
    points_awarded = 0;
    league_standings = l2.get_standings();
    for(auto it = league_standings.begin(); it != league_standings.end(); it++)
    {
        points_awarded += it->second;
    }
    REQUIRE(points_awarded == 0);
}
