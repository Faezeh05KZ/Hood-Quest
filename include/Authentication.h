#ifndef AUTHENTICATION_HPP
#define AUTHENTICATION_HPP

#include <iostream>
#include <string>

#include "User.h"

class UserStorage ;

class Authentication 
{
    private:

        UserStorage& userStorage ;

        std::string hashPassword(const std::string& Password) const ;
        bool isCredentialInputValid(const std::string& username, const std::string& password) const ;
        bool Whitespace_Only(const std::string& text) const ;

    public:

        explicit Authentication(UserStorage& userStorage) ;

        bool registerUser(const std::string& username, const std::string& password) ;
        User* login(const std::string& username, const std::string& password) ;

    bool verify_Password(const User& user, const std::string& rawPassword) const ;
};

#endif
