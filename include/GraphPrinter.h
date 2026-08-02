#ifndef GRAPHPRINTER_H
#define GRAPHPRINTER_H

#include "Graph.h"

class GraphPrinter
{
public:

    GraphPrinter() = default;
    void printGraph(const Graph& graph) const;

private:

    void printMap(const Graph& graph) const;

};

#endif