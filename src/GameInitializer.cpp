#include "GameInitializer.h"
#include <cstdlib>
#include <ctime>
#include <vector>

void GameInitializer::initializeGame(GameState &state, const Graph &graph)
{
    state.setGraph(&graph);

    const std::string GoTherTOWin = "V";

    std::string playerPos = randomVertex(graph, GoTherTOWin, "");

    std::string wolfPos = randomVertex(graph, GoTherTOWin, playerPos);

    state.reset(playerPos, wolfPos);
}

std::string GameInitializer::randomVertex(const Graph &g, const std::string &ExceptWinCell, const std::string &ExceptPlayerCell)
{
    const auto &verts = g.getVertices();

    std::vector<std::string> validCells;

    for (const auto &v : verts)
    {
        std::string id = v.getId();
        if (id != ExceptWinCell && id != ExceptPlayerCell)
        {
            validCells.push_back(id);
        }
    }

    if (validCells.empty())
    {
        return "";
    }

    int randomIndex = rand() % validCells.size();
    
    return validCells[randomIndex];
}