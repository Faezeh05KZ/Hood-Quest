#include "BST.h"

using namespace std ;

BST::BST() : root(nullptr) {}

BST::~BST()
{

    clearNode(root) ;

}

BST::BSTNode* BST::insertNode(BST::BSTNode* node, User* user)
{

    if (node == nullptr)
    {
        return new BSTNode(user) ;
    }

    if (user->getUsername() < node->user->getUsername())
    {
        node->left = insertNode(node->left, user) ;
    }
    else if (user->getUsername() > node->user->getUsername())
    {
        node->right = insertNode(node->right, user) ;
    }
    else
    {
        node->user = user ;
    }

    return node ;

}

BST::BSTNode* BST::findNode(BST::BSTNode* node, const string& username) const
{

    if (node == nullptr)
    {
        return nullptr ;
    }

    if (username == node->user->getUsername())
    {
        return node ;
    }

    if (username < node->user->getUsername())
    {
        return findNode(node->left, username) ;
    }

    return findNode(node->right, username) ;

}

void BST::clearNode(BST::BSTNode* node)
{

    if (node == nullptr)
    {
        return ;
    }

    clearNode(node->left) ;
    clearNode(node->right) ;

    delete node ;

}

void BST::insert(User* user)
{

    if (user == nullptr)
    {
        return ;
    }

    root = insertNode(root, user) ;

}

User* BST::search(const string& username) const
{

    BSTNode* node = findNode(root, username) ;

    if (node == nullptr)
    {
        return nullptr ;
    }

    return node->user ;

}

int BST::getScore(const string& username) const
{

    User* user = search(username) ;

    if (user == nullptr)
    {
        return -1 ;
    }

    return user->getTotalScore() ;

}
