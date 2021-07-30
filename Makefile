# -*- MakeFile -*-

all: server client

server: server.o board.o player.o
	g++ -std=c++17 server.o board.o player.o -o server -pthread -lssl -lcrypto

server.o: server.cpp player.h board.h
	g++ -std=c++17 -c server.cpp -pthread -lssl -lcrypto

player.o: player.cpp player.h
	g++ -std=c++17 -c player.cpp

board.o: board.cpp board.h player.h
	g++ -std=c++17 -c board.cpp

client: client.o
	g++ -std=c++17 client.o -o client -pthread -lssl -lcrypto

client.o: client.cpp
	g++ -std=c++17 -c client.cpp -pthread -lssl -lcrypto

clean:
	rm -f *.o server client