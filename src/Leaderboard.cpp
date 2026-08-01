#include <iostream>

#include "Leaderboard.h"

using namespace std;

Leaderboard::Leaderboard(Heap& scoreHeap) : scoreHeap(scoreHeap) {}

void Leaderboard::refresh(User* user)
{

    if (user == nullptr)
    {
        return ;
    }

    scoreHeap.updateScore(user) ;

}

bool Leaderboard::hasTopPlayer() const
{

    return !scoreHeap.isEmpty() ;

}

User* Leaderboard::getTopPlayer() const
{

    return scoreHeap.getTopPlayer() ;

}

void Leaderboard::showTopPlayer() const
{

    if (!hasTopPlayer())
    {

        cout << "No players have been registered yet !!" << endl ;
        return ;

    }

    User* topPlayer = getTopPlayer() ;

    cout << " Top Player: " << topPlayer->getUsername() << " - Score: " << topPlayer->getTotalScore() << endl ;

}
