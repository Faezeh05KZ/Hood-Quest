#include "Stack.h"

using namespace std ;

Stack::Node::Node(const GameState& value) : data(value), next(nullptr) {}

Stack::Stack() : head(nullptr), count(0) {}

Stack::~Stack()
{
    clear() ;
}

bool Stack::isEmpty() const
{
    return head == nullptr ;
}

int Stack::size() const
{
    return count ;
}

void Stack::push(const GameState& state)
{
    Node* node = new Node(state) ;
    node->next = head ;
    head = node ;

    ++count ;
}

void Stack::pop()
{
    if (isEmpty())
    {
        return ;
    }

    Node* temp = head ;
    head = head->next ;

    delete temp ;

    --count ;
}

GameState& Stack::top()
{
    return head->data ;
}

const GameState& Stack::top() const
{
    return head->data ;
}

void Stack::clear()
{
    while (!isEmpty())
    {
        pop() ;
    }
}
