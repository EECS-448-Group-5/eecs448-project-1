Battleship: Player.o HardAI.o EasyAI.o MediumAI.o ship.o main.o game.o board.o Executive.o
	g++ -std=c++11 -g -Wall HardAI.o EasyAI.o MediumAI.o ship.o main.o game.o board.o Executive.o -o Battleship
main.o: main.cpp Executive.h
	g++ -std=c++11 -g -Wall -c main.cpp
Executive.o: Executive.cpp Executive.h
	g++ -std=c++11 -g -Wall -c Executive.cpp
board.o: board.cpp board.h
	g++ -std=c++11 -g -Wall -c board.cpp
ship.o: ship.cpp ship.h
	g++ -std=c++11 -g -Wall -c ship.cpp
game.o: game.cpp  game.h
	g++ -std=c++11 -g -Wall -c game.cpp
Player.o: Player.cpp Player.h
	g++ -std=c++11 -g -Wall -c Player.cpp
MediumAI.o: MediumAI.cpp MediumAI.h
	g++ -std=c++11 -g -Wall -c MediumAI.cpp
EasyAI.o: EasyAI.cpp EasyAI.h
	g++ -std=c++11 -g -Wall -c EasyAI.cpp
HardAI.o: HardAI.cpp HardAI.h
	g++ -std=c++11 -g -Wall -c HardAI.cpp
clean:
	rm *.o Battleship
winclean:
	del *.o Battleship.exe
