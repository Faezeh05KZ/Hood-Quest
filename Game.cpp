#include "Game.h"
#include "GameInitializer.h"
#include "GameLoop.h"
#include "TurnManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "GraphBuilder.h"
#include "MoveManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() : auth(), leaderboard(auth)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    GraphBuilder builder;
    graph = builder.buildGraph();
}

void Game::start()
{
    Renderer::renderWelcome();
    mainMenuLoop();
}

void Game::run()
{
    start();
}

void Game::mainMenuLoop()
{
    while (true)
    {
        Renderer::renderMainMenu();
        int choice = InputManager::readMenuChoice(1, 3);
        switch (choice)
        {
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

void Game::handleRegister()
{
    Renderer::renderRegistrationPrompt();
    std::string username = InputManager::readString();

    if (username.empty())
    {
        Renderer::renderError("Username cannot be empty.");
        return;
    }

    std::cout << "  Password: ";
    std::string password = InputManager::readString(false);

    if (password.empty())
    {
        Renderer::renderError("Password cannot be empty.");
        return;
    }

    if (auth.registerUser(username, password))
    {
        Renderer::renderMessage("Account created! Welcome, " + username + "!");
    }
    else
    {
        Renderer::renderError("Username '" + username + "' already exists. Try a different name.");
    }
}

void Game::handleLogin()
{
    Renderer::renderLoginPrompt();
    std::string username = InputManager::readString();

    std::cout << "  Password: ";
    std::string password = InputManager::readString(false);

    UserRecord rec;
    if (!auth.login(username, password, rec))
    {
        Renderer::renderError("Invalid username or password.");
        return;
    }

    Renderer::renderUserInfo(rec.username, rec.totalScore);
    HeapEntry top = auth.getTopPlayer();
    Renderer::renderTopPlayer(top.username, top.score);

    while (true)
    {
        std::cout << "\n  What would you like to do?\n";
        std::cout << "  1. Play a new game\n";
        std::cout << "  2. Search score by username (BST)\n";
        std::cout << "  3. View leaderboard\n";
        std::cout << "  4. Logout\n";
        std::cout << "  > ";
        int choice = InputManager::readMenuChoice(1, 4);

        if (choice == 1)
        {
            playGame(username);
            HeapEntry newTop = auth.getTopPlayer();
            Renderer::renderTopPlayer(newTop.username, newTop.score);
        }
        else if (choice == 2)
        {
            showBSTSearch();
        }
        else if (choice == 3)
        {
            leaderboard.displayTop(10);
        }
        else
        {
            Renderer::renderMessage("Logged out.");
            break;
        }
    }
}

void Game::playGame(const std::string &username)
{
    GameState state;
    GameInitializer::initializeGame(state, graph);
    UndoManager undoManager;
    MoveManager moveManager(state, undoManager);
    Renderer::renderMessage("\n  === NEW GAME STARTED ===");
    Renderer::renderMessage("  Red Hood starts at [" + state.getPlayer().getPosition() +
                            "], Wolf at [" + state.getWolf().getPosition() +
                            "], Goal: [V]");

    TurnManager turnManager(state, moveManager, undoManager, username);
    GameLoop gameLoop(turnManager);

    gameLoop.run(state, username);
    int roundScore = state.getScore();
    auth.updateScore(username, roundScore);

    UserRecord updated;
    auth.getUserInfo(username, updated);
    Renderer::renderMessage("  Total score updated to: " + std::to_string(updated.totalScore));
}

void Game::showBSTSearch()
{
    std::cout << "\n  Enter username to search: ";
    std::string name = InputManager::readString();
    BSTEntry entry;
    if (auth.searchBST(name, entry))
    {
        std::cout << "  Found: " << entry.username << " -> Score: " << entry.score << "\n";
    }
    else
    {
        Renderer::renderError("User '" + name + "' not found in BST.");
    }
}