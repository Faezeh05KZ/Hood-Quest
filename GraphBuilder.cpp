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
    graph.addVertex(Vertex("A"));
    graph.addVertex(Vertex("B"));
    graph.addVertex(Vertex("C"));
    graph.addVertex(Vertex("D"));
    graph.addVertex(Vertex("E"));
    graph.addVertex(Vertex("F"));
    graph.addVertex(Vertex("G"));
    graph.addVertex(Vertex("J"));
    graph.addVertex(Vertex("K"));
    graph.addVertex(Vertex("W"));
    graph.addVertex(Vertex("M"));
    graph.addVertex(Vertex("O"));
    graph.addVertex(Vertex("P"));
    graph.addVertex(Vertex("R"));
    graph.addVertex(Vertex("S"));
    graph.addVertex(Vertex("Q"));
    graph.addVertex(Vertex("T"));
    graph.addVertex(Vertex("U"));
    graph.addVertex(Vertex("V", VertexType::Goal));

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