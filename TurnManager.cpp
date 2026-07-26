#include "TurnManager.h"
#include <cstdlib>
#include <iostream>
#include <string>

TurnManager::TurnManager(GameState &state, MoveManager &moveManager, UndoManager &undoManager, const std::string &username)
    : state(state), moveManager(moveManager), undoManager(undoManager),
      username(username), lastMoveWasUndo(false) {}

int TurnManager::rollDice()
{
    return (rand() % 6) + 1;
}

bool TurnManager::executeTurn()
{
    lastMoveWasUndo = false;

    Renderer::clearScreen();
    Renderer::renderGameHeader(state, username);
    Renderer::renderMap(state);

    undoManager.saveState(state);

    std::string playerPos = state.getPlayer().getPosition();
    auto suggestedPath = moveManager.suggestedPath(playerPos);
    std::string suggestedNext = moveManager.suggestedMove(playerPos);
    auto validMoves = moveManager.validMoves(playerPos);

    Renderer::renderTurnInfo(state, suggestedPath, suggestedNext, validMoves);

    bool gameOver = playerPhase(suggestedNext, validMoves);
    if (gameOver)
        return false;

    if (!lastMoveWasUndo)
    {
        wolfPhase();

        if (GameRules::checkGameOver(state))
        {
            if (GameRules::checkLose(state))
            {
                state.setStatus(GameStatus::Lost);
            }
            return false;
        }
    }

    state.nextTurn();
    return true;
}

bool TurnManager::playerPhase(const std::string &suggestedNext, const std::vector<std::string> &validMoves)
{
    while (true)
    {
        Renderer::renderMoveOptions(validMoves, suggestedNext, undoManager.canUndo());

        std::string input;
        std::getline(std::cin, input);

        bool valid = false;
        std::string choice = InputManager::parseMoveInput(
            input, validMoves, suggestedNext, undoManager.canUndo(), valid);

        if (!valid)
        {
            Renderer::renderError("Invalid move! Enter a valid adjacent vertex, 'D' for suggestion, or 'U' to undo.");
            continue;
        }

        if (choice == "U" || choice == "u")
        {
            if (!undoManager.canUndo())
            {
                Renderer::renderError("Nothing to undo.");
                continue;
            }

            state = undoManager.undo();

            ScoreManager::applyUndoPenalty(state);
            Renderer::renderScoreDelta(-2, "Undo penalty");

            lastMoveWasUndo = true;
            return false;
        }

        bool followedSuggestion = (choice == suggestedNext);

        state.getPlayer().setPosition(choice);
        ScoreManager::awardMoveScore(state, followedSuggestion);
        Renderer::renderScoreDelta(
            followedSuggestion ? ScoreManager::SFollowDijkstra : ScoreManager::SValidMove,
            followedSuggestion ? "Followed Dijkstra" : "Custom move");

        if (GameRules::checkWin(state))
        {
            ScoreManager::awardWinBonus(state);
            Renderer::renderScoreDelta(ScoreManager::SWin, "Reached Grandma's house!");
            state.setStatus(GameStatus::Won);
            return true;
        }

        if (GameRules::checkLose(state))
        {
            state.setStatus(GameStatus::Lost);
            return true;
        }

        return false;
    }
}

void TurnManager::wolfPhase()
{
    std::string wolfPos = state.getWolf().getPosition();
    std::string playerPos = state.getPlayer().getPosition();

    int dice = rollDice();
    bool wolfCanMove = (dice % 2 == 0);

    std::string wolfDest = wolfPos;
    bool actuallyMoved = false;

    if (wolfCanMove)
    {
        std::string next = moveManager.wolfNextMove(wolfPos, playerPos);
        if (!next.empty() && next != wolfPos)
        {
            state.getWolf().setPosition(next);
            wolfDest = next;
            actuallyMoved = true;
        }
    }

    Renderer::renderWolfMove(wolfPos, wolfDest, actuallyMoved, dice);
}