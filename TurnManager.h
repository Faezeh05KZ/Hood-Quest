#ifndef TURNMANAGER_H
#define TURNMANAGER_H

#include "GameState.h"
#include "GameRules.h"
#include "ScoreManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "MoveManager.h"
#include "UndoManager.h"
#include "Dijkstra.h"
#include "Constant.h"
#include <string>
#include <vector>

class TurnManager {
public:
    TurnManager(GameState& state, MoveManager& moveManager, UndoManager& undoManager, const std::string& username);

    bool executeTurn();

private:
    GameState& state;
    MoveManager& moveManager;
    UndoManager& undoManager;
    std::string username;

    bool lastMoveWasUndo;

    bool playerPhase(const std::string& suggestedNext, const std::vector<std::string>& validMoves);

    void wolfPhase();

    int rollDice();
};

#endif
