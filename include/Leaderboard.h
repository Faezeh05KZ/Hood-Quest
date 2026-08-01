#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include "Heap.h"
#include "User.h"

class Leaderboard
{
    private:

        Heap& scoreHeap ;

    public:

        explicit Leaderboard(Heap& scoreHeap) ;

        void refresh(User* user) ;

        bool hasTopPlayer() const ;
        User* getTopPlayer() const ;

        void showTopPlayer() const ;

};

#endif
