#include <iostream>
#include "player.h"

enum Cell {EMPTY, BLOCK, PLAYER};

class Board {
public:
    Board();
    bool setBlock(int, int);
    bool setPlayer(Player*, int); //0-right 1-up 2-left 3-down
private:
    Cell** gameBoard;
    Player* gamePlayer[4];
};