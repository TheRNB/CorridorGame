#include <iostream>
#include "board.h"

Board::Board(int plNumber) {
    playerNumber = plNumber;
    boardSize = 11;
    gameBoard = new Cell* [boardSize];
    for (int i = 0; i < boardSize; ++i) {
        gameBoard[i] = new Cell [boardSize];
        for (int j = 0; j < boardSize; ++j) {
            gameBoard[i][j] = EMPTY;
        }
    }

    for (int i = 0; i < 4; ++i)
        gamePlayer[i] = NULL;
}

bool Board::setBlock(int X, int Y, Direction direction) {
    int XDiff = 0, YDiff = 0;
    if (direction == LEFT or direction == RIGHT)
        YDiff = 1;
    else if (direction == UP or direction == DOWN)
        XDiff = 1;

    bool isPossible = true;
    for (int i = -1; i <= 1; ++i) {
        if (((X+(XDiff*i)) >= 0) and ((X+(XDiff*i)) < boardSize) and ((Y+(YDiff*i)) >= 0) and (Y+(YDiff*i) < boardSize) and
            (gameBoard[X+(XDiff*i)][Y+(YDiff*i)] == EMPTY) and 
            !(((X+(XDiff*i)) == int(boardSize/2)) and ((Y+(YDiff*i)) == int(boardSize/2))))
            isPossible &= true;
        else
            isPossible = false;
    }

    if (isPossible == false)
        return false;

    for (int i = -1; i <= 1; ++i) {
        gameBoard[X+(XDiff*i)][Y+(YDiff*i)] = BLOCK;
    }
    return true;
}

void Board::startPlayer(int id) {
    gamePlayer[id] = new Player(id);
    if (id == 0) {
        gameBoard[0][0] = PLAYER1;
        gamePlayer[id]->setPos(0, 0);
    } else if (id == 1) {
        gameBoard[boardSize - 1][boardSize - 1] = PLAYER2;
        gamePlayer[id]->setPos(boardSize - 1, boardSize - 1);
    } else if (id == 2) {
        gameBoard[boardSize - 1][0] = PLAYER3;
        gamePlayer[id]->setPos(boardSize - 1, 0);
    } else if (id == 3) {
        gameBoard[0][boardSize - 1] = PLAYER4;
        gamePlayer[id]->setPos(0, boardSize - 1);
    }

    return;
}

bool Board::isValidCell(Player& currPlayer, Direction direction) {
    int xDiff = 0, yDiff = 0;
    if (direction == RIGHT) yDiff = 1;
    else if (direction == UP) xDiff = -1;
    else if (direction == LEFT) yDiff = -1;
    else if (direction == DOWN) xDiff = 1;

    if (currPlayer.getPosX()+xDiff < 0 or currPlayer.getPosX()+xDiff >= boardSize)
        return false;
    if (currPlayer.getPosY()+yDiff < 0 or currPlayer.getPosY()+yDiff >= boardSize)
        return false;
    
    return true;
}

bool Board::setPlayer(Player& currPlayer, Direction direction) {
    bool isPossible = false;
    int xDiff = 0, yDiff = 0;
    if (direction == RIGHT) yDiff = 1;
    else if (direction == UP) xDiff = -1;
    else if (direction == LEFT) yDiff = -1;
    else if (direction == DOWN) xDiff = 1;
    
    int currX = currPlayer.getPosX(), currY = currPlayer.getPosY();
    //std::cerr << "we want to move " << currPlayer.getId() << " from " << currX << " " << currY << std::endl;
    if (isValidCell(currPlayer, direction) and gameBoard[currX+xDiff][currY+yDiff] == EMPTY) {
        gameBoard[currX+xDiff][currY+yDiff]
         = gameBoard[currX][currY];
        gameBoard[currX][currY] = EMPTY;
        currPlayer.setPos(currX+xDiff, currY+yDiff);
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

int Board::whichInMiddle() {
    ////std::cerr << "middle: " << gameBoard[int(boardSize/2)][int(boardSize/2)] << std::endl;
    if (gameBoard[int(boardSize/2)][int(boardSize/2)] == PLAYER1)
        return 1;
    if (gameBoard[int(boardSize/2)][int(boardSize/2)] == PLAYER2)
        return 2;
    if (gameBoard[int(boardSize/2)][int(boardSize/2)] == PLAYER3)
        return 3;
    if (gameBoard[int(boardSize/2)][int(boardSize/2)] == PLAYER4)
        return 4;
    return 0;
}

int Board::getPlayerAmount() {
    return playerNumber;
}

void Board::savePlayer(Player* pl, int id) {
    gamePlayer[id] = pl;
    return;
}

Player* Board::getPlayer(int id) {
    ////std::cerr << "The called ID was " << id << std::endl;
    return gamePlayer[id];
}
