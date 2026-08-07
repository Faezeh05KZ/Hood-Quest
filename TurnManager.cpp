#include "TurnManager.h"
#include <cstdlib>
#include <iostream>
#include <string>

TurnManager::TurnManager(GameState& state, MoveManager& moveManager, UndoManager& undoManager, const std::string& username)
    : state(state), moveManager(moveManager), undoManager(undoManager),
      username(username), lastMoveWasUndo(false) {}

int TurnManager::rollDice() {
    return (rand() % 6) + 1;
}

bool TurnManager::executeTurn() {
    lastMoveWasUndo = false;

    Renderer::clearScreen();
    Renderer::renderGameHeader(state, username);
    Renderer::renderMap(state);

    std::string playerPos = state.getPlayer().getPosition();
    PathResult suggestedPath = Dijkstra::findShortestPath(*state.getGraph(), playerPos, "V");
    std::string suggestedNext = moveManager.getSuggestedNextMove();
    std::vector<std::string> validMoves = moveManager.getValidMoves();

    Renderer::renderTurnInfo(state, suggestedPath.path, suggestedNext, validMoves);
    moveManager.showSuggestedAStarPath();

    bool gameOver = playerPhase(suggestedNext, validMoves);
    if (gameOver) {
        return false;
    }

    if (!lastMoveWasUndo) {
        wolfPhase();

        if (GameRules::checkGameOver(state)) {
            if (GameRules::checkLose(state)) {
                state.setStatus(GameStatus::Lost);
            }
            return false;
        }
    }

    state.nextTurn();
    return true;
}

bool TurnManager::playerPhase(const std::string& suggestedNext, const std::vector<std::string>& validMoves) {
    while (true) {
        Renderer::renderMoveOptions(validMoves, suggestedNext, undoManager.canUndo());

        std::string input;
        std::getline(std::cin, input);

        bool valid = false;
        std::string choice = InputManager::parseMoveInput(
            input, validMoves, suggestedNext, undoManager.canUndo(), valid);

        if (!valid) {
            Renderer::renderError("Invalid move! Enter a valid adjacent vertex, 'GO' for the suggested move, or 'UNDO' to undo.");
            continue;
        }

        if (choice == "UNDO") {

            state = undoManager.undo();
            ScoreManager::applyUndoPenalty(state);
            Renderer::renderScoreDelta(ScoreManager::SUndo, "Undo penalty");

            lastMoveWasUndo = true;
            return false;
        }

        bool followedSuggestion = (choice == suggestedNext);

        undoManager.saveState(state);

        if (!moveManager.movePlayer(choice)) {

            Renderer::renderError("Move could not be applied.");
            continue;
        }
        ScoreManager::awardMoveScore(state, followedSuggestion);
        Renderer::renderScoreDelta(
            followedSuggestion ? ScoreManager::SFollowDijkstra : ScoreManager::SValidMove,
            followedSuggestion ? "Followed Dijkstra" : "Custom move");

        if (GameRules::checkWin(state)) {
            ScoreManager::awardWinBonus(state);
            Renderer::renderScoreDelta(ScoreManager::SWin, "Reached Grandma's house!");
            state.setStatus(GameStatus::Won);
            return true;
        }

        if (GameRules::checkLose(state)) {
            state.setStatus(GameStatus::Lost);
            return true;
        }

        return false;
    }
}

void TurnManager::wolfPhase() {
    std::string wolfPos = state.getWolf().getPosition();

    int dice = rollDice();
    bool wolfCanMove = (dice % 2 == 0);
    bool actuallyMoved = false;

    if (wolfCanMove) {
        moveManager.moveWolf();
        actuallyMoved = (state.getWolf().getPosition() != wolfPos);
    }

    Renderer::renderWolfMove(wolfPos, state.getWolf().getPosition(), actuallyMoved, dice);
}
