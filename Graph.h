#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_map>

#include "Vertex.h"
#include "Edge.h"

struct Neighbor
{
    std::string vertexName;
    int weight;
};

class Graph
{
private:

    std::vector<Vertex> vertices;
    std::vector<Edge> edges;

    std::unordered_map<
        std::string,
        std::vector<Neighbor>
    > adjacencyList;

    static const std::vector<Neighbor> EMPTY_NEIGHBORS;

public:

    Graph();

    bool addVertex(const Vertex& vertex);
    bool addEdge(const Edge& edge);
    bool removeVertex(const std::string& vertexName);
    bool removeEdge(const std::string& source, const std::string& destination);
    Vertex* findVertex(const std::string& vertexName);
    bool hasVertex(const std::string& vertexName) const;
    bool hasEdge(const std::string& source, const std::string& destination) const;
    const std::vector<Vertex>& getVertices() const;
    const std::vector<Edge>& getEdges() const;
    const std::vector<Neighbor>&
    getNeighbors(const std::string& vertexName) const;
};

#endif