#include <iostream>
#include <cmath>
#include "board.h"
#include "utils/stringFunctions.h"

Board::Board(int plNumber) {
    playerNumber = plNumber;
    boardSize = 11;
    gameBoard = new Cell* [boardSize];
    isPassed = new bool* [boardSize];
    for (int i = 0; i < boardSize; ++i) {
        gameBoard[i] = new Cell [boardSize];
        isPassed[i] = new bool [boardSize];
        for (int j = 0; j < boardSize; ++j) {
            gameBoard[i][j] = EMPTY;
            isPassed[i][j] = false;
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

    if (isConnected(X, Y, direction) == false)
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

bool Board::isConnected(int X, int Y, Direction direction) {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            isPassed[i][j] = ((gameBoard[i][j]==BLOCK)?true:false);
        }
    }

    int XDiff = 0, YDiff = 0;
    if (direction == LEFT or direction == RIGHT)
        YDiff = 1;
    else if (direction == UP or direction == DOWN)
        XDiff = 1;
    
    for (int i = -1; i <= 1; ++i) {
        if (((X+(XDiff*i)) >= 0) and ((X+(XDiff*i)) < boardSize) and ((Y+(YDiff*i)) >= 0) and (Y+(YDiff*i) < boardSize) and
            (gameBoard[X+(XDiff*i)][Y+(YDiff*i)] == EMPTY) and 
            !(((X+(XDiff*i)) == int(boardSize/2)) and ((Y+(YDiff*i)) == int(boardSize/2))))
            isPassed[X+(XDiff*i)][Y+(YDiff*i)] = true;
    }

    dfs(0, 0);

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (isPassed[i][j] == false) {
                return false;
            }
        }
    }

    return true;
}

void Board::dfs(int X, int Y) {
    isPassed[X][Y] = true;
    
    int XDiff[] = {1, 0, -1, 0};
    int YDiff[] = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
        if ((X + XDiff[i]) >= 0 and (X + XDiff[i]) < boardSize 
        and (Y + YDiff[i]) >= 0 and (Y + YDiff[i]) < boardSize
        and isPassed[X + XDiff[i]][Y + YDiff[i]] == false) {
            dfs(X+XDiff[i], Y+YDiff[i]);
        }
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

        std::string num = int2String(boardSize-i);
        while ((int)num.size() < 2) 
            num += " ";

        currSituation += num;
        for (int j = 0; j < boardSize; ++j) {
            if (i == boardSize/2 and j == boardSize/2) {
                currSituation += "☒ ";
            }
            else if (gameBoard[i][j] == EMPTY)
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

    currSituation += "  ";
    
    for (int i = 1; i <= boardSize; ++i) {
        std::string tmp = int2String(i);

        while ((int)tmp.size() < 2) 
            tmp += " ";
        
        currSituation += tmp;
    }

    currSituation += "\n";

    return currSituation;
}

int Board::whichInMiddle() {
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
    return gamePlayer[id];
}

double Board::getDistance(Player* pl) {
    int mid = (boardSize/2);
    double distance = sqrt(pow(mid-pl->getPosX(), 2) + pow(mid-pl->getPosY(), 2));
    return distance;
}
