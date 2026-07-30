#ifndef MOVEMANAGER_H
#define MOVEMANAGER_H

#include <string>
#include "GameState.h"
#include "BFS.h"
#include "Dijkstra.h"

class MoveManager{
private:

    GameState& gameState;
    BFS bfs;

public:

    MoveManager(GameState& state);
    bool movePlayer(const std::string& destination);
    void moveWolf();
    void showSuggestedPath() const;
    void showSuggestedAStarPath() const;
    std::vector<std::string> getValidMoves() const;
    std::string getSuggestedNextMove() const;
  
};

#endif