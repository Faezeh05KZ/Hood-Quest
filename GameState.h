#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include "Player.h"
#include "Wolf.h"
#include "Graph.h"


using namespace std;

enum class GameStatus { Playing, Won, Lost };


class GameState {
private:
    int playerPos;
    int wolfPos;
    int score;
    int turnNumber;
    bool gameOver;
    bool gameActive;

public:


};


#endif
