#include "Renderer.h"
#include <iostream>
#include <iomanip>

void Renderer::renderWelcome()
{
    std::cout << "\n";
    std::cout << "  ██╗  ██╗ ██████╗  ██████╗ ██████╗  ██████╗ ██╗   ██╗███████╗███████╗████████╗\n";
    std::cout << "  ██║  ██║██╔═══██╗██╔═══██╗██╔══██╗██╔═══██╗██║   ██║██╔════╝██╔════╝╚══██╔══╝\n";
    std::cout << "  ███████║██║   ██║██║   ██║██║  ██║██║   ██║██║   ██║█████╗  ███████╗   ██║   \n";
    std::cout << "  ██╔══██║██║   ██║██║   ██║██║  ██║██║▄▄ ██║██║   ██║██╔══╝  ╚════██║   ██║   \n";
    std::cout << "  ██║  ██║╚██████╔╝╚██████╔╝██████╔╝╚██████╔╝╚██████╔╝███████╗███████║   ██║   \n";
    std::cout << "  ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═════╝  ╚══▀▀═╝  ╚═════╝ ╚══════╝╚══════╝   ╚═╝   \n";
    std::cout << "\n           The Algorithm Forest  --  Help Red Riding Hood reach Grandma!\n\n";
}

void Renderer::renderSeparator()
{
    std::cout << "  +---------------------------------------------------------+\n";
}

void Renderer::renderMainMenu()
{
    renderSeparator();
    std::cout << "  |                     MAIN MENU                          |\n";
    renderSeparator();
    std::cout << "  |  1. Register new account                               |\n";
    std::cout << "  |  2. Login to existing account                          |\n";
    std::cout << "  |  3. Exit                                               |\n";
    renderSeparator();
    std::cout << "  Your choice: ";
}

void Renderer::renderRegistrationPrompt()
{
    std::cout << "\n  --- Register ---\n";
    std::cout << "  Username: ";
}

void Renderer::renderLoginPrompt()
{
    std::cout << "\n  --- Login ---\n";
    std::cout << "  Username: ";
}

void Renderer::renderUserInfo(const std::string &username, int totalScore)
{
    std::cout << "\n  Welcome back, " << username << "!\n";
    std::cout << "  Your total score: " << totalScore << "\n";
}

void Renderer::renderTopPlayer(const std::string &topName, int topScore)
{
    std::cout << "\n  +------------------------------+\n";
    std::cout << "  |  CURRENT TOP PLAYER          |\n";
    std::cout << "  |  " << std::left << std::setw(20) << topName
              << " " << std::right << std::setw(5) << topScore << "  |\n";
    std::cout << "  +------------------------------+\n";
}

void Renderer::renderGameHeader(const GameState &state, const std::string &username)
{
    std::cout << "\n";
    renderSeparator();
    std::cout << "  |  Player: " << std::left << std::setw(12) << username
              << "  Score: " << std::setw(5) << state.getScore()
              << "  Turn: " << std::setw(3) << state.getTurnNumber() << "   |\n";
    std::cout << "  |  Red Riding Hood: [" << state.getPlayer().getPosition()
              << "]    Wolf: [" << state.getWolf().getPosition()
              << "]    Goal: [V]              |\n";
    renderSeparator();
}

void Renderer::renderMap(const GameState &state)
{
    const Graph *g = state.getGraph();
    if (!g)
        return;

    std::string player = state.getPlayer().getPosition();
    std::string wolf = state.getWolf().getPosition();

    std::cout << "\n  Map nodes  ( [R]=Red Hood  [W]=Wolf  [G]=Grandma )\n";
    std::cout << "  ";
    for (const auto &v : g->getVertices())
    {
        std::string id = v.getId();
        std::cout << id;
        if (id == player && id == wolf)
            std::cout << "[R+W] ";
        else if (id == player)
            std::cout << "[R]   ";
        else if (id == wolf)
            std::cout << "[W]   ";
        else if (id == "V")
            std::cout << "[G]   ";
        else
            std::cout << "      ";
    }
    std::cout << "\n";

    std::cout << "  Edges: ";
    for (const auto &edge : g->getEdges())
    {
        std::cout << edge.getSource() << "-" << edge.getDestination() << "(" << edge.getWeight() << ") ";
    }
    std::cout << "\n";
}

void Renderer::renderTurnInfo(const GameState &state, const std::vector<std::string> &suggestedPath, const std::string &suggestedNext, const std::vector<std::string> &validMoves)
{
    std::cout << "\n  Dijkstra suggested path to Grandma's house:\n  ";
    for (size_t i = 0; i < suggestedPath.size(); ++i)
    {
        std::cout << suggestedPath[i] << (i + 1 < suggestedPath.size() ? " -> " : "");
    }
    std::cout << "\n  Suggested next move: [" << suggestedNext << "]\n";
    std::cout << "  Your valid moves: ";
    for (const auto &move : validMoves)
        std::cout << "[" << move << "] ";
    std::cout << "\n";
}

void Renderer::renderMoveOptions(const std::vector<std::string> &validMoves, const std::string &suggestedNext, bool canUndo)
{
    std::cout << "\n  Enter your choice:\n";
    std::cout << "    - A vertex name for a valid move (";
    for (const auto &move : validMoves)
        std::cout << move << " ";
    std::cout << ")\n";
    std::cout << "    - 'D' to follow Dijkstra suggestion [" << suggestedNext << "]\n";
    if (canUndo)
        std::cout << "    - 'U' to Undo last turn (-2 score)\n";
    std::cout << "  > ";
}

void Renderer::renderWolfMove(const std::string &wolfFrom, const std::string &wolfTo, bool moved, int diceRoll)
{
    std::cout << "\n  [Wolf] Dice rolled: " << diceRoll;
    if (moved)
        std::cout << " (even) -> Wolf moves from [" << wolfFrom << "] to [" << wolfTo << "]\n";
    else
        std::cout << " (odd) -> Wolf stays at [" << wolfFrom << "]\n";
}

void Renderer::renderScoreDelta(int delta, const std::string &reason)
{
    std::cout << "  Score " << (delta >= 0 ? "+" : "") << delta << "  (" << reason << ")\n";
}

void Renderer::renderGameOver(const GameState &state, const std::string &username)
{
    std::cout << "\n";
    renderSeparator();
    if (state.getStatus() == GameStatus::Won)
    {
        std::cout << "  |           *** YOU WIN! ***                           |\n";
        std::cout << "  |  Red Riding Hood reached Grandma's house!            |\n";
    }
    else
    {
        std::cout << "  |           *** GAME OVER ***                          |\n";
        std::cout << "  |  The wolf caught Red Riding Hood!                    |\n";
    }
    std::cout << "  |  " << username << "'s score this round: " << state.getScore() << "\n";
    renderSeparator();
}

void Renderer::renderError(const std::string &msg)
{
    std::cout << "  [!] " << msg << "\n";
}

void Renderer::renderMessage(const std::string &msg)
{
    std::cout << "  " << msg << "\n";
}