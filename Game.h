#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "Graph.h"
#include "MoveManager.h"
#include "Authentication.h"
#include "UndoManager.hpp"
#include "Leaderboard.h"
#include <string>

class Game {
public:
    Game();

    void start();

    void run();

private:
    Authentication auth;

    Leaderboard leaderboard;

    Graph graph;

    void mainMenuLoop();

    void handleRegister();

    void handleLogin();

    void playGame(const std::string& username);
    
    void showBSTSearch();
};

#endif 