#ifndef UNDOMANAGER_HPP
#define UNDOMANAGER_HPP

#include "Stack.h"
#include "GameState.h"

class UndoManager
{
    private:

        Stack historyStack ;
        static const int UNDO_PENALTY = 2 ;

    public:

        UndoManager() ;

        UndoManager(const UndoManager& other) = delete ;
        UndoManager& operator=(const UndoManager& other) = delete ;

        void saveState(const GameState& state) ;

        bool canUndo() const ;
        GameState undo() ;

        int getUndoPenalty() const ;

};

#endif
