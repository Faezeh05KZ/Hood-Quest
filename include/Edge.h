#ifndef EDGE_H
#define EDGE_H

#include <string>

class Edge{
private:
    std::string source;
    std::string destination;
    int weight;

public:

    Edge();
    Edge(const std::string& source, const std::string& destination, int weight = 1);
    std::string getSource() const;
    std::string getDestination() const;
    int getWeight() const;
    void setWeight(int weight);
};

#endif