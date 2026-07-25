#include "GameRules.h"

bool GameRules::checkWin(const GameState &state)
{
    const std::string GoTherTOWin = "V";

    return (state.getPlayerPosition() == GoTherTOWin) && !checkLose(state);
}

bool GameRules::checkLose(const GameState &state)
{
    return state.areColliding();
}

bool GameRules::checkGameOver(const GameState &state)
{
    return checkWin(state) || checkLose(state);
}

bool GameRules::checkPlayerEnteredWolfVertex(const GameState &state)
{
    return state.areColliding();
}

bool GameRules::isValidMove(const GameState &state, const std::string &targetVertex)
{
    const Graph *graph = state.getGraph();
    if (!graph)
    {
        return false;
    }
    std::string currentPos = state.getPlayerPosition();
    return graph->hasEdge(currentPos, targetVertex);
}