# -*- MakeFile -*-

all: server client

server: server.o board.o player.o stringFunctions.o jsonResponseContainers.o
	g++ -std=c++17 server.o board.o player.o stringFunctions.o  jsonResponseContainers.o -o server -lpthread -lssl -lcrypto

server.o: server.cpp player.h board.h utils/stringFunctions.h
	g++ -std=c++17 -c server.cpp -lpthread -lssl -lcrypto

player.o: player.cpp player.h
	g++ -std=c++17 -c player.cpp

board.o: board.cpp board.h player.h
	g++ -std=c++17 -c board.cpp

client: client.o stringFunctions.o  jsonResponseContainers.o
	g++ -std=c++17 client.o stringFunctions.o  jsonResponseContainers.o -o client -lpthread -lssl -lcrypto

client.o: client.cpp
	g++ -std=c++17 -c client.cpp -lpthread -lssl -lcrypto

stringFunctions.o: utils/stringFunctions.cpp utils/stringFunctions.h
	g++ -std=c++17 -c utils/stringFunctions.cpp

jsonResponseContainers.o: utils/jsonResponseContainers.cpp utils/jsonResponseContainers.h utils/stringFunctions.h
	g++ -std=c++17 -c utils/jsonResponseContainers.cpp


test: test-main.o catch.o jsonResponseContainers-test.o stringFunctions-test.o board-test.o player-test.o jsonResponseContainers.o stringFunctions.o board.o player.o
	g++ -std=c++17 test-main.o catch.o jsonResponseContainers-test.o stringFunctions-test.o board-test.o player-test.o jsonResponseContainers.o stringFunctions.o board.o player.o -o testFile
	./testFile
	rm -f *.o testFile

catch.o: test/catch.cpp
	g++ -std=c++17 -c test/catch.cpp

test-main.o: test/test-main.cpp
	g++ -std=c++17 -c test/test-main.cpp

jsonResponseContainers-test.o: test/jsonResponseContainers-test.cpp utils/jsonResponseContainers.h
	g++ -std=c++17 -c test/jsonResponseContainers-test.cpp

stringFunctions-test.o: test/stringFunctions-test.cpp utils/stringFunctions.h
	g++ -std=c++17 -c test/stringFunctions-test.cpp

board-test.o: test/board-test.cpp board.h
	g++ -std=c++17 -c test/board-test.cpp

player-test.o: test/player-test.cpp player.h
	g++ -std=c++17 -c test/player-test.cpp

clean:
	rm -f *.o server client testFile
