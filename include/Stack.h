#ifndef STACK_HPP
#define STACK_HPP

#include "GameState.h"

class Stack
{

    private:

        struct Node
        {
            GameState data ;
            Node* next ;

            Node(const GameState& value) ;
        } ;

        Node* head ;
        int count ;

    public:

        Stack() ;
        ~Stack() ;

        Stack(const Stack& other) = delete ;
        Stack& operator=(const Stack& other) = delete ;

        bool isEmpty() const ;

        int size() const ;

        void push(const GameState& state) ;
        void pop() ;

        GameState& top() ;
        const GameState& top() const ;

        void clear() ;

};
#endif