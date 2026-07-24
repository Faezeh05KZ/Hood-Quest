#include "Wolf.h"

Wolf::Wolf() : position(0) {}

Wolf::Wolf(int startPos) : position(startPos) {}

int Wolf::getPosition() const {
    return position;
}

void Wolf::setPosition(int pos) {
    position = pos;
}

void Wolf::reset(int startPos) {
    position = startPos;
}