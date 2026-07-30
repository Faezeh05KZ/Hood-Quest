#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <string>
#include <vector>

#include "User.h"

class HashTable
{
    private:

        struct HashNode
        {
            User* user ;
            HashNode* next ;

            HashNode(User* u) : user(u), next(nullptr) {}
        };

        static const int TABLE_SIZE = 101 ;
        HashNode** buckets ;

        int hashFunction(const std::string& username) const ;

    public:

        HashTable() ;
        ~HashTable() ;

        HashTable(const HashTable& other) = delete ;
        HashTable& operator=(const HashTable& other) = delete ;

        bool insert(User* user) ;
        User* search(const std::string& username) const ;
        bool exists(const std::string& username) const ;

        std::vector<User*> getAllUsers() const ;

};

#endif