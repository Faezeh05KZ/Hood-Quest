#include "MinHeap.h"

#include <algorithm>
#include <stdexcept>

bool MinHeap::empty() const{
    return heap.empty();
}

size_t MinHeap::size() const{
    return heap.size();
}

bool MinHeap::contains(const std::string& vertex) const{
    return position.find(vertex) != position.end();
}

void MinHeap::swapNodes(size_t first, size_t second){
    std::swap(heap[first], heap[second]);
    position[heap[first].vertex] = first;
    position[heap[second].vertex] = second;
}

void MinHeap::heapifyUp(size_t index){
    while (index > 0){
        size_t parent = (index - 1) / 2;

        if (heap[parent].priority <= heap[index].priority){
            break;
        }

        swapNodes(parent, index);
        index = parent;
    }
}

void MinHeap::heapifyDown(size_t index){
    const size_t heapSize = heap.size();

    while (true){
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t smallest = index;

        if (left < heapSize &&
            heap[left].priority < heap[smallest].priority){
            smallest = left;
        }

        if (right < heapSize &&
            heap[right].priority < heap[smallest].priority){
            smallest = right;
        }

        if (smallest == index){
            break;
        }

        swapNodes(index, smallest);
        index = smallest;
    }
}

void MinHeap::insert(const std::string& vertex, int priority){
    if (contains(vertex)){
        return;
    }

    heap.emplace_back(vertex, priority);
    size_t index = heap.size() - 1;
    position[vertex] = index;
    heapifyUp(index);
}

std::string MinHeap::extractMin(){
    if (empty()){
        throw std::runtime_error("Heap is empty.");
    }

    std::string minVertex = heap.front().vertex;
    position.erase(minVertex);

    if (heap.size() == 1){
        heap.pop_back();
        return minVertex;
    }

    heap.front() = heap.back();
    position[heap.front().vertex] = 0;
    heap.pop_back();
    heapifyDown(0);
    return minVertex;
}

void MinHeap::decreaseKey(const std::string& vertex, int newPriority){
    auto it = position.find(vertex);

    if (it == position.end()){
        return;
    }

    size_t index = it->second;

    if (newPriority >= heap[index].priority){
        return;
    }

    heap[index].priority = newPriority;
    heapifyUp(index);
}