![alt text](https://raw.githubusercontent.com/TheRNB/CorridorGame/main/logo.png)
# Quoridor Game #
This is a spin on the board game "Quoridor". The general rules of the game are:
- Each player can do 2 things in their move:
    - Either move their bead to an unblocked cell adjacent to their current cell.
    - Or they can choose a cell and block that cell with either the cells to its left and right, or the cells to its up and down.
- A cell is deemed 'unblocked' if:
    - No player (including the current player) has blocked that cell in a previous turn.
    - No other players are in that cell.
    - The cell is not out of bounds!
- The goal of the game is to get to the middle cell in the board. The first player who gets there wins the game.

### Installation ###
#### Cloning the project ####
```
git clone https://github.com/TheRNB/CorridorGame.git
```

#### Compiling the project ####
```
make all
```

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