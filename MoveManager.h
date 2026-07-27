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

    MoveManager(GameState& state, UndoManager& undoManager);
    bool movePlayer(const std::string& destination);
    void moveWolf();
    void showSuggestedPath() const;
    std::vector<std::string> getValidMoves() const;
    std::string getSuggestedNextMove() const;
  
};

#endif