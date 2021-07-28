#include <iostream>
#include "board.h"

Board::Board() {
    boardSize = 11;
    gameBoard = new Cell* [boardSize];
    for (int i = 0; i < boardSize; ++i)
        gameBoard[i] = new Cell [boardSize];

    for (int i = 0; i < 3; ++i)
        gamePlayer[i] = NULL;
}

bool Board::setBlock(int X, int Y) {
    if (gameBoard[X][Y] == EMPTY) {
        gameBoard[X][Y] = BLOCK;
        return true;
    } else
        return false;
}

bool Board::setPlayer(Player* currPlayer, int direction) { //0-right 1-up 2-left 3-down
    bool isPossible = false;
    if (direction == 0 and gameBoard[currPlayer->getPosX()+1][currPlayer->getPosY()] == EMPTY) {
        gameBoard[currPlayer->getPosX()][currPlayer->getPosY()] = EMPTY;
        gameBoard[currPlayer->getPosX()+1][currPlayer->getPosY()] = PLAYER;
        currPlayer->setPos(currPlayer->getPosX()+1, currPlayer->getPosY());
        isPossible = true;
    } 
    else if (direction == 1 and gameBoard[currPlayer->getPosX()][currPlayer->getPosY()+1] == EMPTY) {
        gameBoard[currPlayer->getPosX()][currPlayer->getPosY()] = EMPTY;
        gameBoard[currPlayer->getPosX()][currPlayer->getPosY()+1] = PLAYER;
        currPlayer->setPos(currPlayer->getPosX(), currPlayer->getPosY()+1);
        isPossible = true;
    } 
    else if (direction == 2 and gameBoard[currPlayer->getPosX()-1][currPlayer->getPosY()] == EMPTY) {
        gameBoard[currPlayer->getPosX()][currPlayer->getPosY()] = EMPTY;
        gameBoard[currPlayer->getPosX()-1][currPlayer->getPosY()] = PLAYER;
        currPlayer->setPos(currPlayer->getPosX()-1, currPlayer->getPosY());
        isPossible = true;
    } 
    else if (direction == 3 and gameBoard[currPlayer->getPosX()][currPlayer->getPosY()-1] == EMPTY) {
        gameBoard[currPlayer->getPosX()][currPlayer->getPosY()] = EMPTY;
        gameBoard[currPlayer->getPosX()][currPlayer->getPosY()-1] = PLAYER;
        currPlayer->setPos(currPlayer->getPosX(), currPlayer->getPosY()-1);
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
                currSituation += "P ";
        }
        currSituation += "\n";
    }

    return currSituation;
}