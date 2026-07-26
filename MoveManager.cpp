#include "MoveManager.h"
#include "GameState.h"
#include "ScoreManager.h"
#include <iostream>

MoveManager::MoveManager(GameState& state, UndoManager& undo)
    : gameState(state), undoManager(undo), bfs(*state.getGraph()){}

void MoveManager::showSuggestedPath() const{
    PathResult path = Dijkstra::findShortestPath( *gameState.getGraph(), gameState.getPlayer().getPosition(), "V");
    if(path.path.empty()){
        std::cout<<"No Path\n";
        return;
    }

    std::cout << "Suggested Path : ";

    for (const auto& vertex : path.path){
        std::cout << vertex << " ";
    }

    std::cout << std::endl;
}

bool MoveManager::movePlayer(const std::string& destination){
    const Graph* graph = gameState.getGraph();

    std::string current = gameState.getPlayer().getPosition();

    if (!graph->hasEdge(current, destination)){
        return false;
    }

    undoManager.saveState(gameState);

    PathResult shortestPath = Dijkstra::findShortestPath(*graph, current,"V");

    bool followedSuggestion = false;

    if (shortestPath.path.size() >= 2){
        followedSuggestion = (shortestPath.path[1] == destination);
    }

    gameState.getPlayer().setPosition(destination);

    ScoreManager::awardMoveScore( gameState, followedSuggestion);

    return true;
}

//حرکت گرگ

bool MoveManager::useUndo(){
    if (!undoManager.canUndo()){
        return false;
    }

    gameState = undoManager.undo();
    ScoreManager::applyUndoPenalty(gameState);

    return true;
}

void MoveManager::playTurn(){
    showSuggestedPath();
    std::string destination;
    std::cin >> destination;

    if (destination == "UNDO"){
        useUndo();
        return;
    }

    if (!movePlayer(destination)){
        std::cout << "Invalid Move\n";
        return;
    }

    if (checkWin()){
        return;
    }

    if (checkLose()){
        return;
    }

    moveWolf();

    if (checkLose()){
        return;
    }

    gameState.nextTurn();
}

bool MoveManager::checkWin(){
    if (gameState.getPlayer().getPosition() == "V"){
        gameState.setStatus(GameStatus::Won);
        ScoreManager::awardWinBonus(gameState);
        return true;
    }

    return false;
}

bool MoveManager::checkLose(){
    if (gameState.areColliding()){
        gameState.setStatus(GameStatus::Lost);
        return true;
    }

    return false;
}