#include "BFS.h"

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

BFS::BFS(const Graph& graph) : graph(graph){}

std::vector<std::string> BFS::findPath(const std::string& start, const std::string& goal) const{
    std::queue<std::string> frontier;
    std::unordered_set<std::string> visited;
    std::unordered_map<std::string, std::string> parent;

    frontier.push(start);
    visited.insert(start);

    while (!frontier.empty()){
        std::string current = frontier.front();
        frontier.pop();

        if (current == goal){
            break;
        }

        const auto& neighbors = graph.getNeighbors(current);

        for (const Neighbor& neighbor : neighbors){
            const std::string& next = neighbor.vertexName;

            if (visited.find(next) != visited.end()){
                continue;
            }

            visited.insert(next);
            parent[next] = current;
            frontier.push(next);
        }
    }

    if (visited.find(goal) == visited.end()){
        return {};
    }

    std::vector<std::string> path;

    for (std::string current = goal;; current = parent[current]){
        path.push_back(current);

        if (current == start){
            break;
        }
    }

    std::reverse(path.begin(), path.end());
    return path;
}

std::string BFS::getNextMove(const std::string& wolf, const std::string& player) const{
    std::vector<std::string> path = findPath(wolf, player);

    if (path.size() < 2){
        return wolf;
    }

    return path[1];
}