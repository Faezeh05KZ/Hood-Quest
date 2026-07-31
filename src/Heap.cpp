#include "Heap.h"

Heap::Heap() : data(nullptr), capacity(8), count(0)
{

    data = new User*[capacity] ;

}

Heap::~Heap()
{

    delete[] data ;

}

void Heap::resize()
{

    int newCapacity = capacity * 2 ;
    User** newData = new User*[newCapacity] ;

    for (int i = 0; i < count; ++i)
    {

        newData[i] = data[i] ;

    }

    delete[] data ;

    data = newData ;
    capacity = newCapacity ;

}

int Heap::parentIndex(int index) const
{

    return (index - 1) / 2 ;

}

int Heap::leftChildIndex(int index) const
{

    return 2 * index + 1 ;

}

int Heap::rightChildIndex(int index) const
{

    return 2 * index + 2 ;

}

void Heap::heapifyUp(int index)
{

    while (index > 0)
    {

        int parent = parentIndex(index) ;

        if (data[parent]->getTotalScore() >= data[index]->getTotalScore())
        {
            break ;
        }

        User* temp = data[parent] ;
        data[parent] = data[index] ;
        data[index] = temp ;

        index = parent ;

    }

}

void Heap::heapifyDown(int index)
{

    while (true)
    {

        int left = leftChildIndex(index) ;
        int right = rightChildIndex(index) ;
        int largest = index ;

        if (left < count && data[left]->getTotalScore() > data[largest]->getTotalScore())
        {
            largest = left ;
        }

        if (right < count && data[right]->getTotalScore() > data[largest]->getTotalScore())
        {
            largest = right ;
        }

        if (largest == index)
        {
            break ;
        }

        User* temp = data[largest] ;
        data[largest] = data[index] ;
        data[index] = temp ;

        index = largest ;

    }

}

int Heap::findIndex(const User* user) const
{

    for (int i = 0; i < count; ++i)
    {

        if (data[i] == user)
        {
            return i ;
        }

    }

    return -1 ;

}

void Heap::insert(User* user)
{

    if (user == nullptr)
    {
        return ;
    }

    if (count == capacity)
    {
        resize() ;
    }

    data[count] = user ;
    heapifyUp(count) ;

    ++count ;

}

void Heap::updateScore(User* user)
{

    int index = findIndex(user) ;

    if (index == -1)
    {
        insert(user) ;
        return ;
    }

    heapifyUp(index) ;
    heapifyDown(index) ;

}

User* Heap::getTopPlayer() const
{

    if (isEmpty())
    {
        return nullptr ;
    }

    return data[0] ;

}

bool Heap::isEmpty() const
{

    return count == 0 ;

}

int Heap::size() const
{

    return count ;

}
