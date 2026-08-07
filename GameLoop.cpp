#include "GameLoop.h"
#include "Renderer.h"

GameLoop::GameLoop(TurnManager &tm) : turnManager(tm), running(false) {}

void GameLoop::run(GameState &state, const std::string &username)
{
    running = true;
    while (running && !state.isGameOver())
    {
        bool continueGame = turnManager.executeTurn();
        if (!continueGame || state.isGameOver())
        {
            running = false;
        }
    }
    if (state.isGameOver())
    {
        Renderer::renderGameOver(state, username);
    }
    else
    {
        Renderer::renderMessage("Game execution stopped.");
    }
}

void GameLoop::stop()
{
    running = false;
}