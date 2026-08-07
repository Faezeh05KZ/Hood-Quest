#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "GameState.h"
#include "TurnManager.h"
#include <string>

class GameLoop
{
private:
    TurnManager &turnManager;

    bool running;

public:
    explicit GameLoop(TurnManager &turnManager);

    ~GameLoop() = default;

    GameLoop(const GameLoop &) = delete;

    GameLoop &operator=(const GameLoop &) = delete;

    void run(GameState &state, const std::string &username);

    void stop();
};

#endif