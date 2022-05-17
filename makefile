elo_test: elo_test.o Team.o Player.o Ligue.o
	g++ -o elo_test.out elo_test.o Team.o Player.o Ligue.o

elo_test.o: elo_test.cpp
	g++ -c elo_test.cpp

Team.o: Team.cpp
	g++ -c Team.cpp

Player.o: Player.cpp
	g++ -c Player.cpp

Ligue.o: Ligue.cpp
	g++ -c Ligue.cpp

# Date.o: Date.cpp
# 	g++ -c Date.cpp

clean:
	rm -f elo_test.out Team.o Player.o Ligue.o