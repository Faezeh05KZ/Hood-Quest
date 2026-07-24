#ifndef ASTAR_H
#define ASTAR_H

#include <string>
#include <vector>
#include "Constant.h"

class Graph;

class AStar{
public:

    static PathResult findShortestPath( const Graph& graph, const std::string& start, const std::string& goal );
    
private:

    static int heuristic( const std::string& current, const std::string& goal );
};

#endif