#ifndef VERTEX_H
#define VERTEX_H

#include <string>

enum class VertexType{
    Normal,
    Goal
};

class Vertex{
private:
    std::string id;
    VertexType type;
    bool visited;

public:
    Vertex();
    Vertex(std::string id, VertexType type = VertexType::Normal);
    const std::string& getId() const;
    VertexType getType() const;
    bool isVisited() const;
    void setVisited(bool state);
    void setType(VertexType type);
};

#endif