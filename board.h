#include <iostream>
#include <string>
#include "player.h"

enum Cell {EMPTY, BLOCK, PLAYER1, PLAYER2, PLAYER3, PLAYER4};
enum Direction {RIGHT, UP, LEFT, DOWN};

class Board {
public:
    Board();
    void startPlayer(Player*);
    bool setBlock(int, int);
    bool setPlayer(Player*, Direction);
    bool isValidCell(Player*, Direction);
    std::string printBoard();
private:
    int boardSize;
    Cell** gameBoard;
    Player* gamePlayer[4];
};