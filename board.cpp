#include <iostream>
#include "board.h"

Board::Board() {
    boardSize = 11;
    gameBoard = new Cell* [boardSize];
    for (int i = 0; i < boardSize; ++i) {
        gameBoard[i] = new Cell [boardSize];
        for (int j = 0; j < boardSize; ++j) {
            gameBoard[i][j] = EMPTY;
        }
    }

    for (int i = 0; i < 3; ++i)
        gamePlayer[i] = NULL;
}

bool Board::setBlock(int X, int Y) {
    if (gameBoard[X][Y] == EMPTY and X != int(boardSize/2) and Y != int(boardSize/2)) {
        gameBoard[X][Y] = BLOCK;
        return true;
    } else
        return false;
}

void Board::startPlayer(Player* currPlayer) {
    if (currPlayer->getId() == 0) {
        gameBoard[0][0] = PLAYER1;
    } else if (currPlayer->getId() == 1) {
        gameBoard[boardSize - 1][boardSize - 1] = PLAYER2;
    } else if (currPlayer->getId() == 2) {
        gameBoard[boardSize - 1][0] = PLAYER3;
    } else if (currPlayer->getId() == 3) {
        gameBoard[0][boardSize - 1] = PLAYER4;
    }

    return;
}

bool Board::isValidCell(Player* currPlayer, Direction direction) {
    int xDiff = 0, yDiff = 0;
    if (direction == RIGHT) xDiff = 1;
    else if (direction == UP) yDiff = 1;
    else if (direction == LEFT) xDiff = -1;
    else if (direction == DOWN) yDiff = -1;

    if (currPlayer->getPosX()+xDiff < 0 or currPlayer->getPosX()+xDiff >= boardSize)
        return false;
    if (currPlayer->getPosY()+yDiff < 0 or currPlayer->getPosY()+yDiff >= boardSize)
        return false;
    
    return true;
}

bool Board::setPlayer(Player* currPlayer, Direction direction) {
    bool isPossible = false;
    int xDiff = 0, yDiff = 0;
    if (direction == RIGHT) xDiff = 1;
    else if (direction == UP) yDiff = 1;
    else if (direction == LEFT) xDiff = -1;
    else if (direction == DOWN) yDiff = -1;
    
    int currX = currPlayer->getPosX(), currY = currPlayer->getPosY();
    if (isValidCell(currPlayer, direction) and gameBoard[currX+xDiff][currY+yDiff] == EMPTY) {
        gameBoard[currX+xDiff][currY+yDiff]
         = gameBoard[currX][currY];
        gameBoard[currX][currY] = EMPTY;
        currPlayer->setPos(currX+xDiff, currY+yDiff);
        isPossible = true;
    }

    return isPossible;
}

std::string Board::printBoard() {
    std::string currSituation = "";
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (gameBoard[i][j] == EMPTY)
                currSituation += "□ ";
            else if (gameBoard[i][j] == BLOCK)
                currSituation += "# ";
            else
                switch(gameBoard[i][j]) {
                    case PLAYER1:
                        currSituation += "A ";
                        break;
                    case PLAYER2:
                        currSituation += "B ";
                        break;
                    case PLAYER3:
                        currSituation += "C ";
                        break;
                    case PLAYER4:
                        currSituation += "D ";
                        break;
                    default:
                        break;
                }
        }
        currSituation += "\n";
    }

    return currSituation;
}
