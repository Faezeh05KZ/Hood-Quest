#include "GraphBuilder.h"

#include <stdexcept>

GraphBuilder::GraphBuilder(){}

Graph GraphBuilder::buildGraph() const{
    Graph graph;
    createGraph(graph);

    if (!validateGraph(graph)){
        throw std::runtime_error("Graph validation failed.");
    }

    return graph;
}

void GraphBuilder::createGraph(Graph& graph) const{
    graph.addVertex(Vertex("A", VertexType::Normal, 1, 4));
    graph.addVertex(Vertex("B", VertexType::Normal, 6, 0));
    graph.addVertex(Vertex("C", VertexType::Normal, 23, 0));
    graph.addVertex(Vertex("D", VertexType::Normal, 39, 0));
    graph.addVertex(Vertex("E", VertexType::Normal, 43, 4));
    graph.addVertex(Vertex("F", VertexType::Normal, 14, 4));
    graph.addVertex(Vertex("G", VertexType::Normal, 30, 4));
    graph.addVertex(Vertex("J", VertexType::Normal, 10, 8));
    graph.addVertex(Vertex("K", VertexType::Normal, 20, 8));
    graph.addVertex(Vertex("W", VertexType::Normal, 30, 8));
    graph.addVertex(Vertex("M", VertexType::Normal, 37, 8));
    graph.addVertex(Vertex("O", VertexType::Normal, 0, 12));
    graph.addVertex(Vertex("P", VertexType::Normal, 10, 12));
    graph.addVertex(Vertex("R", VertexType::Normal, 20, 12));
    graph.addVertex(Vertex("S", VertexType::Normal, 37, 12));
    graph.addVertex(Vertex("Q", VertexType::Normal, 5, 16));
    graph.addVertex(Vertex("T", VertexType::Normal, 20, 16));
    graph.addVertex(Vertex("U", VertexType::Normal, 37, 16));
    graph.addVertex(Vertex("V", VertexType::Goal, 20, 21));

    graph.addEdge(Edge("A", "B", 3));
    graph.addEdge(Edge("A", "F", 6));
    graph.addEdge(Edge("B", "C", 2));
    graph.addEdge(Edge("C", "D", 5));
    graph.addEdge(Edge("D", "E", 1));
    graph.addEdge(Edge("E", "G", 3));
    graph.addEdge(Edge("G", "F", 4));
    graph.addEdge(Edge("G", "M", 4));
    graph.addEdge(Edge("G", "W", 5));
    graph.addEdge(Edge("F", "J", 6));
    graph.addEdge(Edge("J", "K", 3));
    graph.addEdge(Edge("J", "P", 5));
    graph.addEdge(Edge("K", "W", 2));
    graph.addEdge(Edge("K", "R", 3));
    graph.addEdge(Edge("W", "M", 3));
    graph.addEdge(Edge("M", "S", 1));
    graph.addEdge(Edge("O", "P", 3));
    graph.addEdge(Edge("O", "Q", 2));
    graph.addEdge(Edge("P", "R", 1));
    graph.addEdge(Edge("R", "T", 4));
    graph.addEdge(Edge("R", "S", 2));
    graph.addEdge(Edge("S", "U", 6));
    graph.addEdge(Edge("U", "T", 2));
    graph.addEdge(Edge("U", "V", 3));
    graph.addEdge(Edge("Q", "T", 5));
    graph.addEdge(Edge("Q", "V", 5));
}

bool GraphBuilder::validateGraph(const Graph& graph) const{
    if (graph.getVertices().empty()){
        return false;
    }

    if (graph.getEdges().empty()){
        return false;
    }

    for (const Edge& edge : graph.getEdges()){
        if (!graph.hasVertex(edge.getSource())){
            return false;
        }

        if (!graph.hasVertex(edge.getDestination())){
            return false;
        }
    }

    return true;
}