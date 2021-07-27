#include <iostream>
#include "player.h"

Player::Player(int newId) {
    playerId = newId;
}

void Player::setPos(int newX, int newY) {
    posX = newX;
    posY = newY;
    return;
}

int Player::getPosX() const {
    return posX;
}

int Player::getPosY() const {
    return posY;
}

int Player::getId() const {
    return playerId;
}