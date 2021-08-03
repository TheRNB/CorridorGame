# -*- MakeFile -*-

all: test testClean server client projectClean

server: server.o board.o player.o stringFunctions.o jsonResponseContainers.o
	g++ -std=c++17 server.o board.o player.o utils/stringFunctions.o  utils/jsonResponseContainers.o -o server -lpthread -lssl -lcrypto

server.o: server.cpp player.h board.h utils/stringFunctions.h
	g++ -std=c++17 -c server.cpp -lpthread -lssl -lcrypto

player.o: player.cpp player.h
	g++ -std=c++17 -c player.cpp

board.o: board.cpp board.h player.h utils/stringFunctions.h
	g++ -std=c++17 -c board.cpp

client: client.o stringFunctions.o  jsonResponseContainers.o
	g++ -std=c++17 client.o utils/stringFunctions.o  utils/jsonResponseContainers.o -o client -lpthread -lssl -lcrypto

client.o: client.cpp
	g++ -std=c++17 -c client.cpp -lpthread -lssl -lcrypto

stringFunctions.o: utils/stringFunctions.cpp utils/stringFunctions.h
	g++ -std=c++17 -c utils/stringFunctions.cpp -o utils/stringFunctions.o

jsonResponseContainers.o: utils/jsonResponseContainers.cpp utils/jsonResponseContainers.h utils/stringFunctions.h
	g++ -std=c++17 -c utils/jsonResponseContainers.cpp -o utils/jsonResponseContainers.o


test: test/test-main.o test/catch.o test/jsonResponseContainers-test.o test/stringFunctions-test.o test/board-test.o test/player-test.o utils/jsonResponseContainers.o utils/stringFunctions.o board.o player.o
	g++ -std=c++17 test/test-main.o test/catch.o test/jsonResponseContainers-test.o test/stringFunctions-test.o test/board-test.o test/player-test.o utils/jsonResponseContainers.o utils/stringFunctions.o board.o player.o -o test/testFile
	test/./testFile

catch.o: test/catch.cpp
	g++ -std=c++17 -c test/catch.cpp -o test/catch.o

test-main.o: test/test-main.cpp
	g++ -std=c++17 -c test/test-main.cpp -o test/test-main.o

jsonResponseContainers-test.o: test/jsonResponseContainers-test.cpp utils/jsonResponseContainers.h
	g++ -std=c++17 -c test/jsonResponseContainers-test.cpp -o test/jsonResponseContainers-test.o

stringFunctions-test.o: test/stringFunctions-test.cpp utils/stringFunctions.h
	g++ -std=c++17 -c test/stringFunctions-test.cpp -o test/stringFunctions-test.o

board-test.o: test/board-test.cpp board.h
	g++ -std=c++17 -c test/board-test.cpp -o test/board-test.o

player-test.o: test/player-test.cpp player.h
	g++ -std=c++17 -c test/player-test.cpp -o test/player-test.o


clean:
	rm -f *.o utils/*.o server client

testClean:
	rm -f test/*.o test/test-main.o test/testFile

projectClean:
	rm -f *.o utils/*.o