#include "Player.h"

Player::Player() : position("") {}

Player::Player(const std::string& startPos) : position(startPos) {}

std::string Player::getPosition() const {
    return position;
}

void Player::setPosition(const std::string& pos) {
    position = pos;
}

void Player::reset(const std::string& startPos) {
    position = startPos;
}