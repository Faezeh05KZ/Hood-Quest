#ifndef GAMERULES_H
#define GAMERULES_H

#include <string>
#include "GameState.h"

class GameRules
{
public:
    static bool checkWin(const GameState &state);

    static bool checkLose(const GameState &state);

    static bool checkGameOver(const GameState &state);

    static bool checkPlayerEnteredWolfVertex(const GameState &state);

    static bool isValidMove(const GameState &state, const std::string &targetVertex);
};

#endif