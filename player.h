#include <iostream>

class Player {
public:
    Player(int);
    void setPos(int, int);
    int getPosX() const;
    int getPosY() const;
    int getId() const;

private:
    int posX, posY;
    int playerId;
};