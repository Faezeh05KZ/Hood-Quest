#ifndef HEAP_HPP
#define HEAP_HPP

#include "User.h"

class Heap
{
    private:

        User** data ;
        int capacity ;
        int count ;

        void resize() ;

        int parentIndex(int index) const ;
        int leftChildIndex(int index) const ;
        int rightChildIndex(int index) const ;

        void heapifyUp(int index) ;
        void heapifyDown(int index) ;

        int findIndex(const User* user) const ;

    public:

        Heap() ;
        ~Heap() ;

        Heap(const Heap& other) = delete ;
        Heap& operator=(const Heap& other) = delete ;

        void insert(User* user) ;
        void updateScore(User* user) ;

        User* getTopPlayer() const ;
        bool isEmpty() const ;
        int size() const ;

};

#endif
