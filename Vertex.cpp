#include "Vertex.h"

Vertex::Vertex(){
    id = "";
    type = VertexType::Normal;
    visited = false;
}

Vertex::Vertex(std::string id, VertexType type){
    this->id = id;
    this->type = type;
    visited = false;
}

const std::string& Vertex::getId() const{
    return id;
}

VertexType Vertex::getType() const{
    return type;
}

bool Vertex::isVisited() const{
    return visited;
}

void Vertex::setVisited(bool state){
    visited = state;
}

void Vertex::setType(VertexType type){
    this->type = type;
}