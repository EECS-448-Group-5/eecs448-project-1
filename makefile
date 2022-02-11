ships: ship.o test.o game.o board.o Executive.o
	g++ -std=c++11 -g -Wall ship.o test.o game.o board.o Executive.o -o ships
test.o: test.cpp ship.h 
	g++ -std=c++11 -g -Wall -c test.cpp
Executive.o: Executive.cpp Executive.h
	g++ -std=c++11 -g -Wall -c Executive.cpp
board.o: board.cpp board.h
	g++ -std=c++11 -g -Wall -c board.cpp
ship.o: ship.cpp ship.h
	g++ -std=c++11 -g -Wall -c ship.cpp
game.o: game.cpp  game.h 
	g++ -std=c++11 -g -Wall -c game.cpp
clean:
	rm *.o ships
