#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include "Graph.h"

class GraphBuilder
{
private:

    void createGraph(Graph& graph) const;
    bool validateGraph(const Graph& graph) const;

public:

    GraphBuilder();
    Graph buildGraph() const;
};

#endif