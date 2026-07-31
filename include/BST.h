#ifndef BST_HPP
#define BST_HPP

#include <string>

#include "User.h"

class BST
{
    private:

        struct BSTNode
        {
            User* user ;
            BSTNode* left ;
            BSTNode* right ;

            BSTNode(User* u) : user(u), left(nullptr), right(nullptr) {}
        };

        BSTNode* root ;

        BSTNode* insertNode(BSTNode* node, User* user) ;
        BSTNode* findNode(BSTNode* node, const std::string& username) const ;
        void clearNode(BSTNode* node) ;

    public:

        BST() ;
        ~BST() ;

        BST(const BST& other) = delete ;
        BST& operator=(const BST& other) = delete ;

        void insert(User* user) ;
        User* search(const std::string& username) const ;
        int getScore(const std::string& username) const ;

};

#endif
