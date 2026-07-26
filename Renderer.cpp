#include "Renderer.h"
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

    std::string player = state.getPlayer().getPosition();
    std::string wolf = state.getWolf().getPosition();

    std::cout << "\n  Map nodes ("
              << Color::RED << " [R]" << Color::RESET << "=Red Hood "
              << Color::YELLOW << " [W]" << Color::RESET << "=Wolf "
              << Color::GREEN << " [G]" << Color::RESET << "=Grandma )\n  ";

    for (const auto &v : g->getVertices())
    {
        std::string id = v.getId();
        std::cout << id;
        if (id == player && id == wolf)
            std::cout << Color::MAGENTA << "[R+W] " << Color::RESET;
        else if (id == player)
            std::cout << Color::RED << "[R]   " << Color::RESET;
        else if (id == wolf)
            std::cout << Color::YELLOW << "[W]   " << Color::RESET;
        else if (id == "V")
            std::cout << Color::GREEN << "[G]   " << Color::RESET;
        else
            std::cout << "      ";
    }
    std::cout << "\n\n";

    std::cout << "  Edges:\n   ";
    int edgeCount = 0;
    for (const auto &edge : g->getEdges())
    {
        std::cout << edge.getSource() << "-" << edge.getDestination() << "(" << edge.getWeight() << ")  ";
        edgeCount++;
        if (edgeCount % 5 == 0)
        {
            std::cout << "\n   ";
        }
    }
    std::cout << "\n";
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