#include "Wolf.h"

Wolf::Wolf() : position("") {}

Wolf::Wolf(const std::string& startPos) : position(startPos) {}

std::string Wolf::getPosition() const {
    return position;
}

void Wolf::setPosition(const std::string& pos) {
    position = pos;
}

void Wolf::reset(const std::string& startPos) {
    position = startPos;
}