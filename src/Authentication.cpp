#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <cstddef>

#include "Authentication.h"
#include "UserStorage.h"

using namespace std;

Authentication::Authentication(UserStorage& userStorage) : userStorage(userStorage) {}

string Authentication::hashPassword(const string& Password) const 
{

    uint64_t hashValue = 1469598103934665603ULL ;
    const uint64_t prime = 1099511628211ULL ;

    for (size_t i = 0 ; i < Password.size() ; ++i) 
    {
        hashValue ^= static_cast<unsigned char> (Password[i]) ;
        hashValue *= prime ;
    }

    ostringstream output ;
    output << hex << setw(16) << setfill('0') << hashValue ;
    return output.str() ;
}

bool Authentication::Whitespace_Only(const string& text) const 
{
    if (text.empty()) 
    {
        return false;
    }

    for (size_t i = 0 ; i < text.size() ; ++i) 
    {
        const char ch = text[i] ;
        if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' && ch != '\f' && ch != '\v') 
        {
            return false;
        }
    }

    return true; 
}

bool Authentication::isCredentialInputValid(const string& username, const string& password) const 
{
    if (username.empty() || password.empty()) 
    {
        return false;
    }

    if (Whitespace_Only(username) || Whitespace_Only(password)) 
    {
        return false ;
    }

    return true;
}

bool Authentication::registerUser(const string& username, const string& password) 
{
    if (!isCredentialInputValid(username, password)) 
    {
        return false ;
    }

    if (userStorage.usernameExists(username)) 
    {
        return false ;
    }

    const string hashedPassword = hashPassword(password) ;
    User newUser(username, hashedPassword, 0) ;

    return userStorage.addUser(newUser) ;
}

User* Authentication::login(const string& username, const string& password) 
{
    if (!isCredentialInputValid(username, password)) 
    {
        return nullptr ;
    }

    User* user = userStorage.findUser(username) ;
    if (user == nullptr) 
    {
        return nullptr ;
    }

    if (!verify_Password(*user, password)) 
    {
        return nullptr;
    }

    return user ;
}

bool Authentication::verify_Password(const User& user, const string& Password) const 
{
    const string hashedPassword = hashPassword(Password) ;

    return user.checkPasswordHash( hashedPassword ) ;
}
