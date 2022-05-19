elo: elo.o Team.o Player.o League.o Match.o
	g++ -o elo.out elo.o Team.o Player.o League.o Match.o

elo_test: elo_test.o Team.o Player.o League.o Match.o
	g++ -o elo_test.out elo_test.o Team.o Player.o League.o Match.o

elo.o: elo.cpp
	g++ -c -g elo.cpp

elo_test.o: elo_test.cpp
	g++ -c -g elo_test.cpp

Team.o: Team.cpp
	g++ -c -g Team.cpp

Player.o: Player.cpp
	g++ -c -g Player.cpp

League.o: League.cpp
	g++ -c -g League.cpp

Match.o: Match.cpp
	g++ -c -g Match.cpp

clean:
	rm -f elo_test.out elo.out elo_test.o elo.o Team.o Player.o League.o Match.o