#include "Dijkstra.h"
#include "Graph.h"
#include "MinHeap.h"

#include <algorithm>
#include <limits>
#include <unordered_map>

PathResult Dijkstra::findShortestPath(const Graph& graph,const std::string& start,const std::string& goal){
    PathResult result;
    result.distance = -1;

    if (!graph.hasVertex(start) || !graph.hasVertex(goal)){
        return result;
    }

    const int INF = std::numeric_limits<int>::max();

    std::unordered_map<std::string, int> distance;
    std::unordered_map<std::string, std::string> parent;
    std::unordered_map<std::string, bool> visited;

    MinHeap heap;

    for (const Vertex& vertex : graph.getVertices()){
        distance[vertex.getId()] = INF;
        visited[vertex.getId()] = false;
    }

    distance[start] = 0;
    heap.insert(start, 0);

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

            int newDistance = distance[current] + neighbor.weight;

            if (newDistance < distance[neighbor.vertexName]){
                distance[neighbor.vertexName] = newDistance;
                parent[neighbor.vertexName] = current;

                if (heap.contains(neighbor.vertexName)){
                    heap.decreaseKey( neighbor.vertexName, newDistance );
                }
                else{
                    heap.insert( neighbor.vertexName, newDistance );
                }
            }
        }
    }

    if (distance[goal] == INF){
        return result;
    }

    result.distance = distance[goal];
    std::string current = goal;

    while (true){
        result.path.push_back(current);

        if (current == start){
            break;
        }

        current = parent[current];
    }

    std::reverse(result.path.begin(), result.path.end());

    return result;
}