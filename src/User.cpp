#include <iostream>
using namespace std;

#include "User.h"

User::User() : username(""), passwordHash(""), totalScore(0) {}

User::User(const string& username, const string& passwordHash, int totalScore): username(username), passwordHash(passwordHash), totalScore(totalScore) {}

const string& User::getUsername() const 
{
    return username ;
}

const string& User::getPasswordHash() const 
{
    return passwordHash ;
}

int User::getTotalScore() const 
{
    return totalScore ;
}

void User::setPasswordHash(const string& newPasswordHash) 
{
    passwordHash = newPasswordHash ;
}

void User::setTotalScore(int New_Tscore) 
{
    totalScore = New_Tscore ;
}

void User::addToTotalScore(int scoreDelta) 
{
    totalScore += scoreDelta ;
}

bool User::checkPasswordHash(const string& candidateHash) const 
{
    return passwordHash == candidateHash ;
}

bool User::isValid() const 
{
    return !username.empty() && !passwordHash.empty() ;
}
