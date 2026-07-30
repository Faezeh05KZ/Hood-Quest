#include "GraphPrinter.h"

#include <iostream>

void GraphPrinter::printGraph(const Graph& graph) const
{
    std::cout << "\n";
    std::cout << "=========== GRAPH ===========\n\n";

    printMap(graph);

    std::cout << "\n";
}

void GraphPrinter::printMap(const Graph&) const
{
    std::cout << "                   2               5      \n";
    std::cout << "         B----------------C---------------D\n";
    std::cout << "        /                                  \\\n";
    std::cout << "     3 /                                    \\ 1\n";
    std::cout << "      /     6              4            3    \\\n";
    std::cout << "     A-----------F----------------G-----------E\n";
    std::cout << "                /                |  \\    \n";
    std::cout << "             6 /                5|   \\ 4  \n";
    std::cout << "              /    3        2    |  3 \\  \n";
    std::cout << "             J---------K---------W------M\n";
    std::cout << "             |         |               | \n";
    std::cout << "            5|       3 |             1 | \n";
    std::cout << "         3   |    1    |        2      |  \n";
    std::cout << "    O--------P---------R---------------S\n";
    std::cout << "     \\                 |               |\n";
    std::cout << "    2 \\              4 |             6 |\n";
    std::cout << "       \\       5       |      2        |\n";
    std::cout << "        Q--------------T---------------U\n";
    std::cout << "         \\                            /\n";
    std::cout << "        5 \\                        3 / \n";
    std::cout << "           \\                        / \n";
    std::cout << "            \\                      / \n";
    std::cout << "             -----------V----------\n";
}