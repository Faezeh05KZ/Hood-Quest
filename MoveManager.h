#ifndef MOVEMANAGER_H
#define MOVEMANAGER_H

#include <string>
#include "GameState.h"
#include "UndoManager.h"
#include "BFS.h"
#include "Dijkstra.h"

class MoveManager{
private:

    GameState& gameState;
    UndoManager& undoManager;
    BFS bfs;

public:

    MoveManager(GameState& state, UndoManager& undo);
    void playTurn();
    bool movePlayer(const std::string& destination);
    void moveWolf();
    bool useUndo();
    void showSuggestedPath() const;
    bool checkWin();
    bool checkLose();
};

#endif