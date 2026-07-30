#include <fstream>
#include <sstream>

#include "UserStorage.h"

using namespace std ;

bool UserStorage::usernameExists(const string& username) const
{
    return userTable.exists(username) ;
}

bool UserStorage::addUser(const User& user)
{
    User* newUser = new User(user) ;

    if (!userTable.insert(newUser))
    {
        delete newUser ;
        return false ;
    }

    return true ;
}

User* UserStorage::findUser(const string& username)
{
    return userTable.search(username) ;
}

bool UserStorage::saveUsers() const
{
    ofstream outputFile(fileName) ;

    if (!outputFile.is_open())
    {
        return false ;
    }

    for (User* user : userTable.getAllUsers())
    {
        outputFile << user->getUsername() << '|'
                    << user->getPasswordHash() << '|'
                    << user->getTotalScore() << '\n' ;
    }

    return true ;
}

bool UserStorage::loadUsers()
{
    ifstream inputFile(fileName) ;

    if (!inputFile.is_open())
    {
        return false ;
    }

    string line ;

    while (getline(inputFile, line))
    {
        if (line.empty())
        {
            continue ;
        }

        stringstream lineStream(line) ;
        string username ;
        string passwordHash ;
        string scoreText ;

        getline(lineStream, username, '|') ;
        getline(lineStream, passwordHash, '|') ;
        getline(lineStream, scoreText, '|') ;

        if (username.empty() || passwordHash.empty() || scoreText.empty())
        {
            continue ;
        }

        const int totalScore = stoi(scoreText) ;
        addUser(User(username, passwordHash, totalScore)) ;
    }

    return true ;
}

std::vector<User*> UserStorage::getAllUsers()
{
    return userTable.getAllUsers() ;
}
