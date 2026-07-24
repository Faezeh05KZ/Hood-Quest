#include "Player.h"

Player::Player() : position(0) {}

Player::Player(int startPos) : position(startPos) {}

int Player::getPosition() const {
    return position;
}

void Player::setPosition(int pos) {
    position = pos;
}

void Player::reset(int startPos) {
    position = startPos;
}