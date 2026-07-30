#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Constant.h"
#include <string>
#include <vector>

class Graph;

class Dijkstra{
public:

    static PathResult findShortestPath( const Graph& graph, const std::string& start, const std::string& goal);
};

#endif