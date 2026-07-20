#include "Graph.h"

#include <algorithm>

const std::vector<Neighbor> Graph::EMPTY_NEIGHBORS = {};

Graph::Graph(){}

bool Graph::addVertex(const Vertex& vertex){
    if (hasVertex(vertex.getId())){
        return false;
    }

    vertices.push_back(vertex);

    adjacencyList[vertex.getId()] = std::vector<Neighbor>();

    return true;
}

bool Graph::addEdge(const Edge& edge){
    if(edge.getSource()==edge.getDestination())
        return false;

    if (!hasVertex(edge.getSource()) || !hasVertex(edge.getDestination())){
        return false;
    }

    if (hasEdge(edge.getSource(), edge.getDestination())){
        return false;
    }

    edges.push_back(edge);

    Neighbor firstNeighbor;
    firstNeighbor.vertexName = edge.getDestination();
    firstNeighbor.weight = edge.getWeight();

    Neighbor secondNeighbor;
    secondNeighbor.vertexName = edge.getSource();
    secondNeighbor.weight = edge.getWeight();

    adjacencyList[edge.getSource()].push_back(firstNeighbor);
    adjacencyList[edge.getDestination()].push_back(secondNeighbor);

    return true;
}

bool Graph::removeVertex(const std::string& vertexName){
    if (!hasVertex(vertexName)){
        return false;
    }

    for (auto it = vertices.begin(); it != vertices.end(); ++it){
        if (it->getId() == vertexName){
            vertices.erase(it);
            break;
        }
    }

    edges.erase(
        std::remove_if(edges.begin(), edges.end(), [&](const Edge& edge){
                return edge.getSource() == vertexName || edge.getDestination() == vertexName;
            }),
        edges.end());

    adjacencyList.erase(vertexName);

    for (auto& entry : adjacencyList){
        auto& neighbors = entry.second;

        neighbors.erase(
            std::remove_if( neighbors.begin(), neighbors.end(), [&](const Neighbor& neighbor) {
                    return neighbor.vertexName == vertexName;}),
            neighbors.end());
    }

    return true;
}

bool Graph::removeEdge(const std::string& source, const std::string& destination){
    if (!hasEdge(source, destination)){
        return false;
    }

    edges.erase(
        std::remove_if( edges.begin(), edges.end(), [&](const Edge& edge) {
                return( edge.getSource() == source && edge.getDestination() == destination) || 
                ( edge.getSource() == destination && edge.getDestination() == source );
            }),
        edges.end());

    auto sourceIt = adjacencyList.find(source);

    if (sourceIt != adjacencyList.end()){
        auto& sourceNeighbors = sourceIt->second;

        sourceNeighbors.erase(
            std::remove_if( sourceNeighbors.begin(), sourceNeighbors.end(), [&](const Neighbor& neighbor) {
                    return neighbor.vertexName == destination;
                }),
            sourceNeighbors.end());
    }

    auto destinationIt = adjacencyList.find(destination);

    if (destinationIt != adjacencyList.end()){
        auto& destinationNeighbors = destinationIt->second;

        destinationNeighbors.erase(
            std::remove_if( destinationNeighbors.begin(), destinationNeighbors.end(), [&](const Neighbor& neighbor) {
                    return neighbor.vertexName == source;
                }),
            destinationNeighbors.end());
    }

    return true;
}

Vertex* Graph::findVertex(const std::string& vertexName){
    for (Vertex& vertex : vertices){
        if (vertex.getId() == vertexName){
            return &vertex;
        }
    }

    return nullptr;
}

bool Graph::hasVertex(const std::string& vertexName) const{
    for (const Vertex& vertex : vertices){
        if (vertex.getId() == vertexName){
            return true;
        }
    }

    return false;
}

bool Graph::hasEdge(const std::string& source, const std::string& destination) const{
    auto it = adjacencyList.find(source);

    if (it == adjacencyList.end()){
        return false;
    }

    for (const Neighbor& neighbor : it->second){
        if (neighbor.vertexName == destination){
            return true;
        }
    }

    return false;
}

const std::vector<Vertex>& Graph::getVertices() const{
    return vertices;
}

const std::vector<Edge>& Graph::getEdges() const{
    return edges;
}

const std::vector<Neighbor>& Graph::getNeighbors(const std::string& vertexName) const{
    auto it = adjacencyList.find(vertexName);

    if (it == adjacencyList.end()){
        return EMPTY_NEIGHBORS;
    }

    return it->second;
}