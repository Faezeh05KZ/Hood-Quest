#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <string>

class User 
{
    private:

        std::string username ;
        std::string passwordHash ;
        int totalScore ;

    public:

        User() ;
        User(const std::string& username, const std::string& passwordHash, int totalScore = 0) ;

        const std::string& getUsername() const ;
        const std::string& getPasswordHash() const ;
        int getTotalScore() const ;

        void setPasswordHash(const std::string& newPasswordHash) ;
        void setTotalScore(int New_Tscore) ;
        void addToTotalScore(int scoreDelta) ;

        bool checkPasswordHash(const std::string& candidateHash) const ;
        bool isValid() const ;
};

#endif
