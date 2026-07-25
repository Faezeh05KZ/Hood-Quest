#ifndef BFS_H
#define BFS_H

#include "Graph.h"
#include <vector>

class BFS{
private:
    const Graph& graph;

public:
    explicit BFS(const Graph& graph);
    std::vector<std::string> findPath(const std::string& start, const std::string& goal) const;
    std::string getNextMove(const std::string& wolf,const std::string& player) const;
};

#endif