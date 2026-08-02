#ifndef MINHEAP_H
#define MINHEAP_H

#include <string>
#include <vector>
#include <unordered_map>

class MinHeap{
private:

    struct Node{
        std::string vertex;
        int priority;

        Node(const std::string& v = "", int p = 0): vertex(v), priority(p){} 
    };

    std::vector<Node> heap;
    std::unordered_map<std::string, size_t> position;

    void heapifyUp(size_t index);
    void heapifyDown(size_t index);
    void swapNodes(size_t first, size_t second);

public:

    MinHeap() = default;
    bool empty() const;
    size_t size() const;
    bool contains(const std::string& vertex) const;
    void insert(const std::string& vertex, int priority);
    std::string extractMin();
    void decreaseKey(const std::string& vertex, int newPriority);
};

#endif