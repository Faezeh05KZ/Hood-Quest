#ifndef USERSTORAGE_HPP
#define USERSTORAGE_HPP

#include <string>
#include <iostream>

#include "HashTable.h"

class UserStorage
{
    private:

        HashTable userTable ;
        const std::string fileName = "users.txt" ;

    public:

        bool usernameExists(const std::string& username) const ;

        bool addUser(const User& user) ;

        User* findUser(const std::string& username) ;

        bool saveUsers() const ;

        bool loadUsers() ;

        std::vector<User*> getAllUsers() ;

};

#endif