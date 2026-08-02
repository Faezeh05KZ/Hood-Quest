#include "Vertex.h"

Vertex::Vertex(){
    id = "";
    type = VertexType::Normal;
    visited = false;
    x = 0 ;
    y = 0 ;
}

Vertex::Vertex(std::string id, VertexType type){
    this->id = id;
    this->type = type;
    visited = false;
    x = 0 ;
    y = 0 ;
}

Vertex::Vertex(std::string id, VertexType type , int x , int y){
    this->id = id;
    this->type = type;
    visited = false;
    this->x = x;
    this->y = y;
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

int Vertex::getX() const{
    return x;
}

int Vertex::getY() const{
    return y;
}

void Vertex::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}