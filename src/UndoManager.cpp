#include "UndoManager.h"

UndoManager::UndoManager() {}

void UndoManager::saveState(const GameState& state)
{

    historyStack.push(state) ;

}

bool UndoManager::canUndo() const
{

    return !historyStack.isEmpty() ;

}

GameState UndoManager::undo()
{

    GameState previousState = historyStack.top() ;

    historyStack.pop() ;

    return previousState ;

}

int UndoManager::getUndoPenalty() const
{

    return UNDO_PENALTY ;

}
