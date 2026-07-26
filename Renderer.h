#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include "GameState.h"
#include "Graph.h"

class Renderer
{
public:
    static void renderWelcome();

    static void renderMainMenu();

    static void renderGameHeader(const GameState &state, const std::string &username);

    static void renderMap(const GameState &state);

    static void renderTurnInfo(const GameState &state, const std::vector<std::string> &suggestedPath, const std::string &suggestedNext, const std::vector<std::string> &validMoves);

    static void renderMoveOptions(const std::vector<std::string> &validMoves, const std::string &suggestedNext, bool canUndo);

    static void renderWolfMove(const std::string &wolfFrom, const std::string &wolfTo, bool moved, int diceRoll);

    static void renderGameOver(const GameState &state, const std::string &username);

    static void renderUserInfo(const std::string &username, int totalScore);

    static void renderTopPlayer(const std::string &topName, int topScore);

    static void renderError(const std::string &msg);

    static void renderMessage(const std::string &msg);

    static void renderRegistrationPrompt();

    static void renderLoginPrompt();

    static void renderSeparator();

    static void renderScoreDelta(int delta, const std::string &reason);
};

#endif