#include "Game.h"

#include "GameInitializer.h"
#include "GameLoop.h"
#include "TurnManager.h"
#include "MoveManager.h"
#include "UndoManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "GraphBuilder.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game()
    : userStorage(), auth(userStorage), scoreHeap(), leaderboard(scoreHeap), scoreTree(), graph() {
    srand(static_cast<unsigned int>(time(nullptr)));

    GraphBuilder builder;
    graph = builder.buildGraph();

    userStorage.loadUsers();
    loadExistingUsersIntoStructures();
}


void Game::loadExistingUsersIntoStructures() {
    for (User* user : userStorage.getAllUsers()) {
        scoreHeap.insert(user);
        scoreTree.insert(user);
    }
}

void Game::run() {
    start();
    userStorage.saveUsers();
}

void Game::start() {
    Renderer::renderWelcome();
    mainMenuLoop();
}

void Game::mainMenuLoop() {
    while (true) {
        Renderer::renderMainMenu();
        int choice = InputManager::readMenuChoice(1, 3);

        switch (choice) {
            case 1:
                handleRegister();
                break;
            case 2:
                handleLogin();
                break;
            case 3:
                Renderer::renderMessage("Goodbye! May Red Riding Hood's path always be safe.");
                return;
        }
    }
}

void Game::handleRegister() {
    Renderer::renderRegistrationPrompt();

    std::cout << "  Username: ";
    std::string username = InputManager::readString();

    if (username.empty()) {
        Renderer::renderError("Username cannot be empty.");
        return;
    }

    std::cout << "  Password: ";
    std::string password = InputManager::readString(false);

    if (password.empty()) {
        Renderer::renderError("Password cannot be empty.");
        return;
    }

    if (!auth.registerUser(username, password)) {
        Renderer::renderError("Username '" + username + "' already exists. Try a different name.");
        return;
    }


    User* newUser = userStorage.findUser(username);
    if (newUser != nullptr) {
        scoreHeap.insert(newUser);
        scoreTree.insert(newUser);
    }

    userStorage.saveUsers();
    Renderer::renderMessage("Account created! Welcome, " + username + "!");
}

void Game::handleLogin() {
    Renderer::renderLoginPrompt();

    std::cout << "  Username: ";
    std::string username = InputManager::readString();

    std::cout << "  Password: ";
    std::string password = InputManager::readString(false);

    User* user = auth.login(username, password);

    if (user == nullptr) {
        Renderer::renderError("Invalid username or password.");
        return;
    }

    Renderer::renderUserInfo(user->getUsername(), user->getTotalScore());

    if (leaderboard.hasTopPlayer()) {
        User* top = leaderboard.getTopPlayer();
        Renderer::renderTopPlayer(top->getUsername(), top->getTotalScore());
    }

    while (true) {
        std::cout << "\n  What would you like to do?\n";
        std::cout << "  1. Play a new game\n";
        std::cout << "  2. Search score by username (BST)\n";
        std::cout << "  3. Show current top player\n";
        std::cout << "  4. Logout\n";
        std::cout << "  > ";

        int choice = InputManager::readMenuChoice(1, 4);

        if (choice == 1) {
            playGame(username);

            if (leaderboard.hasTopPlayer()) {
                User* newTop = leaderboard.getTopPlayer();
                Renderer::renderTopPlayer(newTop->getUsername(), newTop->getTotalScore());
            }
        } else if (choice == 2) {
            showBSTSearch();
        } else if (choice == 3) {
            leaderboard.showTopPlayer();
        } else {
            Renderer::renderMessage("Logged out.");
            break;
        }
    }
}

void Game::playGame(const std::string& username) {
    User* user = userStorage.findUser(username);
    if (user == nullptr) {
        Renderer::renderError("User not found.");
        return;
    }

    GameState state;
    GameInitializer::initializeGame(state, graph);

    UndoManager undoManager;
    MoveManager moveManager(state);

    Renderer::renderMessage("\n  === NEW GAME STARTED ===");
    Renderer::renderMessage("  Red Hood starts at [" + state.getPlayer().getPosition() +
                             "], Wolf at [" + state.getWolf().getPosition() +
                             "], Goal: [V]");

    TurnManager turnManager(state, moveManager, undoManager, username);
    GameLoop gameLoop(turnManager);

    gameLoop.run(state, username);

    int roundScore = state.getScore();
    user->addToTotalScore(roundScore);

    leaderboard.refresh(user);
    scoreTree.insert(user);
    userStorage.saveUsers();

    Renderer::renderMessage("  Total score updated to: " + std::to_string(user->getTotalScore()));
}

void Game::showBSTSearch() {
    std::cout << "\n  Enter username to search: ";
    std::string name = InputManager::readString();

    User* found = scoreTree.search(name);

    if (found != nullptr) {
        std::cout << "  Found: " << found->getUsername() << " -> Score: " << found->getTotalScore() << "\n";
    } else {
        Renderer::renderError("User '" + name + "' not found in BST.");
    }
}
