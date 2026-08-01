#include "HashTable.h"

using namespace std;

HashTable::HashTable()
{

    buckets = new HashNode*[TABLE_SIZE];

    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        buckets[i] = nullptr ;
    }

}

HashTable::~HashTable()
{

    for (int i = 0; i < TABLE_SIZE; i++)
    {

        HashNode* current = buckets[i];

        while (current != nullptr)
        {

            HashNode* temp = current ;

            current = current->next ;

            delete temp->user ;
            delete temp ;

        }

    }

    delete[] buckets ;

}

int HashTable::hashFunction(const string& username) const
{

    int hash = 0 ;

    for (char ch : username)
    {

        hash = (hash * 31 + ch) % TABLE_SIZE ;

    }

    return hash ;

}

bool HashTable::insert(User* user)
{

    if (user == nullptr)
    {
        return false ;
    }

    if (exists(user->getUsername()))
    {
        return false ;
    }

    int index = hashFunction(user->getUsername()) ;

    HashNode* newNode = new HashNode(user) ;

    newNode->next = buckets[index] ;

    buckets[index] = newNode ;

    return true ;

}

User* HashTable::search(const string& username) const
{

    int index = hashFunction(username) ;

    HashNode* current = buckets[index] ;

    while (current != nullptr)
    {

        if (current->user->getUsername() == username)
        {
            return current->user ;
        }

        current = current->next ;

    }

    return nullptr ;

}

bool HashTable::exists(const string& username) const
{

    return search(username) != nullptr ;

}

vector<User*> HashTable::getAllUsers() const
{

    vector<User*> allUsers ;

    for (int i = 0; i < TABLE_SIZE; ++i)
    {

        HashNode* current = buckets[i] ;

        while (current != nullptr)
        {

            allUsers.push_back(current->user) ;
            current = current->next ;

        }

    }

    return allUsers ;

}