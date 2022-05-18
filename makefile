elo: elo.o Team.o Player.o League.o Match.o
	g++ -o elo.out elo.o Team.o Player.o League.o

elo_test: elo_test.o Team.o Player.o League.o Match.o
	g++ -o elo_test.out elo_test.o Team.o Player.o League.o Match.o

elo.o: elo.cpp
	g++ -c elo.cpp

elo_test.o: elo_test.cpp
	g++ -c elo_test.cpp

Team.o: Team.cpp
	g++ -c Team.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

League.o: League.cpp
	g++ -c League.cpp

Match.o: Match.cpp
	g++ -c Match.cpp

clean:
	rm -f elo_test.out elo.out elo_test.o elo.o Team.o Player.o League.o Match.o