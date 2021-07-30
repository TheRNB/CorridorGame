#include <iostream>
#include <string>
#include "player.h"

enum Cell {EMPTY, BLOCK, PLAYER1, PLAYER2, PLAYER3, PLAYER4};
enum Direction {RIGHT, UP, LEFT, DOWN};

class Board {
public:
    Board(int = 4);
    void startPlayer(Player*);
    bool setBlock(int, int, Direction);
    bool setPlayer(Player*, Direction);
    bool isValidCell(Player*, Direction);
    Cell whichInMiddle();
    std::string printBoard();
    int getPlayerAmount();
    void savePlayer(Player*, int);
private:
    int boardSize;
    int playerNumber;
    Cell** gameBoard;
    Player* gamePlayer[4];
};