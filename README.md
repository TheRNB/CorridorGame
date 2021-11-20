![alt text](https://raw.githubusercontent.com/TheRNB/CorridorGame/main/logo.png)
# Quoridor Game #
Ever wished you could play [Quoridor](https://en.wikipedia.org/wiki/Quoridor) online with friends? Well, now you can! This is an online implementation of the game using C++ and [cpp-httplib](https://github.com/yhirose/cpp-httplib).

### Here's a quick tutorial: ###
Each player is initially spawned in one of the corners of a 11*11 board.
- They can do 2 things in their move:
    - Move their bead to an empty cell adjacent to their current cell.
    - Place a 3-cell-long horizontal block or a 3-cell-long vertical block by choosing its middle cell. 
- A cell is deemed 'empty' if:
    - No player (including the current player) has placed a block that covers that cell in a previous turn.
    - No other player are currently in that cell.
The goal of the game is to get to the middle cell of the board. The first player who gets there wins the game.

### Installation ###
#### Cloning the project ####
```
git clone https://github.com/TheRNB/CorridorGame.git
```
#### Compiling the project ####
```
make all
```

### Execution ###
#### Running the server ####
to run the server, open a terminal and type in:
```
./server
```
you can then choose the number of players and connect to the server via the clients.

#### Running the clients ####
to run the clients, open a terminal and type in:
```
./client
```
the clients will automatically connect to the server. The game will start when all the players connect to the server.
### Developing ###
#### Tests ####
All the parts of the project are made with tests in mind. Tests were created using [Catch2](https://github.com/catchorg/Catch2) and you can run them by typing the following command in terminal:
```
make test
```
The tests include all the parts and you can add extra tests for the parts you develop later.
#### Server Responses ####
The clients communicate with the server using JSON, if you have problems with the server you can check the responses through this address:
```
127.0.0.1:8000
```
#### openssl/err.h ####
If you're experiencing problems with opensll/err.h library, you can install it via the following command:
```
sudo apt-get install libssl-dev
```

### Contributors: ###
This project was mainly developed by [Aaron Bateni](https://github.com/TheRNB).