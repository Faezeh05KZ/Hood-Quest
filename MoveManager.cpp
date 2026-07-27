#include "MoveManager.h"
#include "GameRules.h"
#include "ScoreManager.h"
#include <iostream>

MoveManager::MoveManager(GameState& state, UndoManager& undoManager)
    : gameState(state), undoManager(undoManager), bfs(*state.getGraph()){}

bool MoveManager::movePlayer(const std::string& destination){
    if (!GameRules::isValidMove(gameState, destination)){
        return false;
    }

    undoManager.saveState(gameState);
    const Graph* graph = gameState.getGraph();
    const std::string current = gameState.getPlayer().getPosition();

    PathResult shortestPath = Dijkstra::findShortestPath(*graph, current,"V");

    bool followedSuggestion = false;

    if (shortestPath.path.size() >= 2){
        followedSuggestion = (shortestPath.path[1] == destination);
    }

    gameState.getPlayer().setPosition(destination);
    ScoreManager::awardMoveScore( gameState, followedSuggestion);

    return true;
}

void MoveManager::moveWolf(){
    std::string nextMove = bfs.getNextMove( gameState.getWolf().getPosition(), gameState.getPlayer().getPosition());

    if (!nextMove.empty()){
        gameState.getWolf().setPosition(nextMove);
    }
}

void MoveManager::showSuggestedPath() const{
    PathResult result = Dijkstra::findShortestPath( *gameState.getGraph(), gameState.getPlayer().getPosition(), "V");

    if (result.path.empty()){
        std::cout << "No Path\n";
        return;
    }

    std::cout << "Suggested Path : ";

    for (const auto& vertex : result.path){
        std::cout << vertex << " ";
    }

    std::cout << std::endl;
}

std::vector<std::string> MoveManager::getValidMoves() const{
    std::vector<std::string> validMoves;

    const auto& neighbors = gameState.getGraph()->getNeighbors( gameState.getPlayer().getPosition());

    for (const auto& neighbor : neighbors){
        validMoves.push_back(neighbor.vertexName);
    }

    return validMoves;
}

std::string MoveManager::getSuggestedNextMove() const{
    PathResult result = Dijkstra::findShortestPath(*gameState.getGraph(),gameState.getPlayer().getPosition(), "V");

    if (result.path.size() < 2){
        return "";
    }

    return result.path[1];
}