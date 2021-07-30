# -*- MakeFile -*-

all: server client

server: server.o board.o player.o
	g++ server.o board.o player.o -o server

server.o: server.cpp player.h board.h
	g++ -c server.cpp -pthread -lssl -lcrypto

player.o: player.cpp player.h
	g++ -c player.cpp

board.o: board.cpp board.h player.h
	g++ -c board.cpp

client: 
	g++ client.o -o client

client.o: client.cpp
	g++ -c client.cpp -pthread -lssl -lcrypto

clean:
	rm -f *.o