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
    int x;
    int y;

public:
    Vertex();
    Vertex(std::string id, VertexType type = VertexType::Normal);
    Vertex(std::string id, VertexType type , int x, int y);
    const std::string& getId() const;
    VertexType getType() const;
    bool isVisited() const;
    void setVisited(bool state);
    void setType(VertexType type);
    int getX() const;
    int getY() const;
    void setPosition(int x, int y);
};

#endif