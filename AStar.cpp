#include "AStar.h"
#include "Graph.h"
#include "MinHeap.h"
#include <algorithm>
#include <limits>
#include <unordered_map>

int AStar::heuristic(const std::string& current, const std::string& goal){
    return 0;
}

PathResult AStar::findShortestPath( const Graph& graph, const std::string& start, const std::string& goal){
    PathResult result;
    result.distance = -1;

    if (!graph.hasVertex(start) || !graph.hasVertex(goal)){
        return result;
    }

    const int INF = std::numeric_limits<int>::max();

    std::unordered_map<std::string, int> gScore;
    std::unordered_map<std::string, std::string> parent;
    std::unordered_map<std::string, bool> visited;

    MinHeap heap;

    for (const Vertex& vertex : graph.getVertices()){
        gScore[vertex.getId()] = INF;
        visited[vertex.getId()] = false;
    }

    gScore[start] = 0;

    heap.insert(start,heuristic(start, goal));

    while (!heap.empty()){
        std::string current = heap.extractMin();

        if (visited[current]){
            continue;
        }

        visited[current] = true;

        if (current == goal){
            break;
        }

        const auto& neighbors = graph.getNeighbors(current);

        for (const Neighbor& neighbor : neighbors){
            if (visited[neighbor.vertexName]){
                continue;
            }

            int tentativeG = gScore[current] + neighbor.weight;

            if (tentativeG < gScore[neighbor.vertexName]){
                gScore[neighbor.vertexName] = tentativeG;

                parent[neighbor.vertexName] = current;

                int priority = tentativeG + heuristic( neighbor.vertexName, goal);

                if (heap.contains(neighbor.vertexName)){
                    heap.decreaseKey( neighbor.vertexName, priority );
                }
                else{
                    heap.insert(neighbor.vertexName, priority );
                }
            }
        }
    }

    if (gScore[goal] == INF){
        return result;
    }

    result.distance = gScore[goal];
    std::string current = goal;

    while (true){
        result.path.push_back(current);

        if (current == start){
            break;
        }

        current = parent[current];
    }

    std::reverse( result.path.begin(), result.path.end());
    return result;
}