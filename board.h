#include <iostream>
#include <string>
#include "player.h"

enum Cell {EMPTY=0, BLOCK, PLAYER1, PLAYER2, PLAYER3, PLAYER4};
enum Direction {RIGHT=0, UP, LEFT, DOWN};

class Board {
public:
    Board(int = 4);
    void startPlayer(int);
    bool setBlock(int, int, Direction);
    bool setPlayer(Player&, Direction);
    bool isValidCell(Player&, Direction);
    int whichInMiddle();
    std::string printBoard();
    int getPlayerAmount();
    void savePlayer(Player*, int);
    Player* getPlayer(int);
    double getDistance(Player*);
    bool isConnected(int, int, Direction);
private:
    Player* gamePlayer[4];
    int boardSize;
    int playerNumber;
    Cell** gameBoard;
    bool** isPassed;
    void dfs(int, int);
};