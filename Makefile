# -*- MakeFile -*-

all: server

server: server.o board.o player.o
	g++ server.o board.o player.o -o server

server.o:
	g++ -c server.cpp -pthread -lssl -lcrypto

player.o: player.cpp
	g++ -c player.cpp

board.o: board.cpp
	g++ -c board.cpp

clean:
	rm -f *.o