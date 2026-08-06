#ifndef GAMEINITIALIZER_H
#define GAMEINITIALIZER_H

#include "GameState.h"
#include "Graph.h"
#include <string>

class GameInitializer
{
public:
    static void initializeGame(GameState &state, const Graph &graph);

private:
    static std::string randomVertex(const Graph &g, const std::string &ExceptWinCell, const std::string &ExceptPlayerCell);
};

#endif