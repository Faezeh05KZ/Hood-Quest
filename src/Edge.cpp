#include "Edge.h"

Edge::Edge(){
    source = "";
    destination = "";
    weight = 1;
}

Edge::Edge(const std::string& source, const std::string& destination, int weight){
    this->source = source;
    this->destination = destination;
    this->weight = weight;
}

std::string Edge::getSource() const{
    return source;
}

std::string Edge::getDestination() const{
    return destination;
}

int Edge::getWeight() const{
    return weight;
}

void Edge::setWeight(int weight){
    this->weight = weight;
}