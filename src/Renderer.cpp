#include "Renderer.h"
#include "GraphPrinter.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

namespace Color
{
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string YELLOW = "\033[33m";
    const std::string GREEN = "\033[32m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string BOLD = "\033[1m";
}

void Renderer::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Renderer::renderWelcome()
{
    clearScreen();
    std::cout << Color::CYAN << Color::BOLD;
    std::cout << "\n";
    std::cout << "  ██╗  ██╗ ██████╗  ██████╗ ██████╗  ██████╗ ██╗   ██╗███████╗███████╗████████╗\n";
    std::cout << "  ██║  ██║██╔═══██╗██╔═══██╗██╔══██╗██╔═══██╗██║   ██║██╔════╝██╔════╝╚══██╔══╝\n";
    std::cout << "  ███████║██║   ██║██║   ██║██║  ██║██║   ██║██║   ██║█████╗  ███████╗   ██║   \n";
    std::cout << "  ██╔══██║██║   ██║██║   ██║██║  ██║██║▄▄ ██║██║   ██║██╔══╝  ╚════██║   ██║   \n";
    std::cout << "  ██║  ██║╚██████╔╝╚██████╔╝██████╔╝╚██████╔╝╚██████╔╝███████╗███████║   ██║   \n";
    std::cout << "  ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═════╝  ╚══▀▀═╝  ╚═════╝ ╚══════╝╚══════╝   ╚═╝   \n";
    std::cout << Color::RESET << Color::BOLD;
    std::cout << "\n           The Algorithm Forest  --  Help Red Riding Hood reach Grandma!\n\n"
              << Color::RESET;
}

void Renderer::renderMainMenu()
{
    renderSeparator();
    std::cout << "  |                  " << Color::BOLD << "MAIN MENU" << Color::RESET << "                        |\n";
    renderSeparator();
    std::cout << "  |  " << Color::GREEN << "1." << Color::RESET << " Create new account                                    |\n";
    std::cout << "  |  " << Color::GREEN << "2." << Color::RESET << " Login to existing account                              |\n";
    std::cout << "  |  " << Color::GREEN << "3." << Color::RESET << " Exit                                                   |\n";
    renderSeparator();
    std::cout << "  > ";
}

void Renderer::renderRegistrationPrompt()
{
    clearScreen();
    renderSeparator();
    std::cout << "  |              " << Color::BOLD << "CREATE NEW ACCOUNT" << Color::RESET << "                        |\n";
    renderSeparator();
    std::cout << "  |  Please choose a unique username and password.          |\n";
    renderSeparator();
}

void Renderer::renderLoginPrompt()
{
    clearScreen();
    renderSeparator();
    std::cout << "  |              " << Color::BOLD << "LOGIN" << Color::RESET << "                                     |\n";
    renderSeparator();
    std::cout << "  |  Enter your credentials to continue.                   |\n";
    renderSeparator();
}

void Renderer::renderUserInfo(const std::string &username, int totalScore)
{
    renderSeparator();
    std::cout << "  |  " << Color::BOLD << "Welcome back, " << Color::CYAN << username << Color::RESET << Color::BOLD << "!" << Color::RESET << "\n";
    std::cout << "  |  Total Score: " << Color::GREEN << totalScore << Color::RESET << "\n";
    renderSeparator();
}

void Renderer::renderTopPlayer(const std::string &topName, int topScore)
{
    std::cout << "\n  " << Color::YELLOW << Color::BOLD << "Top Player:" << Color::RESET
              << " " << Color::CYAN << topName << Color::RESET
              << " (Score: " << Color::GREEN << topScore << Color::RESET << ")\n";
}

void Renderer::renderTurnInfo(const GameState &state, const std::vector<std::string> &suggestedPath, const std::string &suggestedNext, const std::vector<std::string> & /* validMoves */)
{
    std::cout << "\n  " << Color::BOLD << "Turn " << state.getTurnNumber() << Color::RESET
              << "  |  Score: " << Color::GREEN << state.getScore() << Color::RESET
              << "  |  Red Hood: [" << Color::RED << state.getPlayer().getPosition() << Color::RESET << "]"
              << "  Wolf: [" << Color::YELLOW << state.getWolf().getPosition() << Color::RESET << "]"
              << "  Goal: [V]\n\n";

    std::cout << "  " << Color::CYAN << "Dijkstra Path:" << Color::RESET << " ";
    for (size_t i = 0; i < suggestedPath.size(); ++i)
    {
        std::cout << suggestedPath[i];
        if (i + 1 < suggestedPath.size())
            std::cout << " -> ";
    }
    std::cout << "\n";

    if (!suggestedNext.empty())
    {
        std::cout << "  " << Color::GREEN << "Suggested next move: [" << suggestedNext << "]" << Color::RESET << "\n";
    }
}

void Renderer::renderMoveOptions(const std::vector<std::string> &validMoves, const std::string &suggestedNext, bool canUndo)
{
    std::cout << "\n  " << Color::BOLD << "Choose your move:" << Color::RESET << "\n";
    std::cout << "  Available moves: ";
    for (size_t i = 0; i < validMoves.size(); ++i)
    {
        if (validMoves[i] == suggestedNext)
            std::cout << Color::GREEN << "[" << validMoves[i] << "]" << Color::RESET;
        else
            std::cout << validMoves[i];
        if (i + 1 < validMoves.size())
            std::cout << ", ";
    }
    std::cout << "\n";
    std::cout << "  " << Color::CYAN << "[GO]" << Color::RESET << " Follow Dijkstra's suggestion";
    if (canUndo)
        std::cout << "  |  " << Color::YELLOW << "[UNDO]" << Color::RESET << " Undo";
    std::cout << "\n";
    std::cout << "  > ";
}

void Renderer::renderWolfMove(const std::string &wolfFrom, const std::string &wolfTo, bool moved, int diceRoll)
{
    std::cout << "\n  " << Color::YELLOW << "Wolf" << Color::RESET << " rolled: " << Color::BOLD << diceRoll << Color::RESET;
    if (moved)
    {
        std::cout << " (even -> moves)  " << wolfFrom << " -> " << Color::YELLOW << wolfTo << Color::RESET << "\n";
    }
    else
    {
        std::cout << " (odd -> stays)  Wolf stays at [" << Color::YELLOW << wolfFrom << Color::RESET << "]\n";
    }
}

void Renderer::renderScoreDelta(int delta, const std::string &reason)
{
    if (delta > 0)
        std::cout << "  " << Color::GREEN << "+" << delta << Color::RESET << " (" << reason << ")\n";
    else if (delta < 0)
        std::cout << "  " << Color::RED << delta << Color::RESET << " (" << reason << ")\n";
    else
        std::cout << "  " << delta << " (" << reason << ")\n";
}

void Renderer::renderSeparator()
{
    std::cout << Color::CYAN << "  +---------------------------------------------------------+\n"
              << Color::RESET;
}

void Renderer::renderGameHeader(const GameState &state, const std::string &username)
{
    renderSeparator();
    std::cout << "  |  Player: " << Color::BOLD << std::left << std::setw(12) << username << Color::RESET
              << "  Score: " << Color::GREEN << std::setw(5) << state.getScore() << Color::RESET
              << "  Turn: " << std::setw(3) << state.getTurnNumber() << "   |\n";

    std::cout << "  |  Red Riding Hood: [" << Color::RED << state.getPlayer().getPosition() << Color::RESET
              << "]    Wolf: [" << Color::YELLOW << state.getWolf().getPosition() << Color::RESET
              << "]    Goal: [" << Color::GREEN << "V" << Color::RESET << "]              |\n";
              
    renderSeparator();
}

void Renderer::renderMap(const GameState &state)
{
    const Graph *g = state.getGraph();
    if (!g)
        return;

    // Print the visual ASCII graph map
    GraphPrinter printer;
    printer.printGraph(*g);

    // Show current positions below the map
    std::string player = state.getPlayer().getPosition();
    std::string wolf = state.getWolf().getPosition();

    std::cout << "  " << Color::RED << "[R]" << Color::RESET << "=Red Hood  "
              << Color::YELLOW << "[W]" << Color::RESET << "=Wolf  "
              << Color::GREEN << "[G]" << Color::RESET << "=Grandma(V)\n";
    std::cout << "  Red Hood: " << Color::RED << player << Color::RESET
              << "  |  Wolf: " << Color::YELLOW << wolf << Color::RESET
              << "  |  Goal: " << Color::GREEN << "V" << Color::RESET << "\n\n";
}

void Renderer::renderGameOver(const GameState &state, const std::string &username)
{
    std::cout << "\n";
    renderSeparator();
    if (state.getStatus() == GameStatus::Won)
    {
        std::cout << Color::GREEN << Color::BOLD;
        std::cout << "  |           *** YOU WIN! ***                           |\n";
        std::cout << "  |  Red Riding Hood reached Grandma's house!            |\n"
                  << Color::RESET;
    }
    else
    {
        std::cout << Color::RED << Color::BOLD;
        std::cout << "  |           *** GAME OVER ***                          |\n";
        std::cout << "  |  The wolf caught Red Riding Hood!                    |\n"
                  << Color::RESET;
    }
    std::cout << "  |  " << username << "'s score this round: " << state.getScore() << "\n";
    renderSeparator();
}

void Renderer::renderError(const std::string &msg)
{
    std::cout << Color::RED << "  [!] " << msg << Color::RESET << "\n";
}

void Renderer::renderMessage(const std::string &msg)
{
    std::cout << "  " << msg << "\n";
}