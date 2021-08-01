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


test: test-main.o jsonResponseContainers-test.o stringFunctions-test.o jsonResponseContainers.o stringFunctions.o
	g++ -c test/catch.cpp
	g++ test-main.o catch.o jsonResponseContainers-test.o stringFunctions-test.o jsonResponseContainers.o stringFunctions.o -o testFile
	./testFile

test-main.o: test/test-main.cpp
	g++ -c test/test-main.cpp

jsonResponseContainers-test.o: test/jsonResponseContainers-test.cpp utils/jsonResponseContainers.h
	g++ -c test/jsonResponseContainers-test.cpp

stringFunctions-test.o: test/stringFunctions-test.cpp utils/stringFunctions.h
	g++ -c test/stringFunctions-test.cpp

clean:
	rm -f *.o server client testFile
