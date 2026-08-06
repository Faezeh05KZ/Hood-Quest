#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "Graph.h"
#include "UserStorage.h"
#include "Authentication.h"
#include "Heap.h"
#include "Leaderboard.h"
#include "BST.h"

class Game {
public:
    Game();

    void run();

private:

    UserStorage userStorage;
    Authentication auth;
    Heap scoreHeap;
    Leaderboard leaderboard;
    BST scoreTree;
    Graph graph;

    void start();
    void mainMenuLoop();
    void handleRegister();
    void handleLogin();
    void playGame(const std::string& username);
    void showBSTSearch();

    void loadExistingUsersIntoStructures();
};

#endif
