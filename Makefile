# -*- MakeFile -*-

all: player.o board.o

player.o: player.cpp
	g++ -c player.cpp

board.o: board.cpp
	g++ -c board.cpp