#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "GameState.h"

class ScoreManager
{
public:
    static const int SFollowDijkstra = 3;
    static const int SValidMove = 1;    
    static const int SUndo = -2;      
    static const int SWin = 5;            

    static void awardFollowDijkstra(GameState &state);
    static void awardValidMove(GameState &state);
    static void applyUndoPenalty(GameState &state);
    static void awardWinBonus(GameState &state);

    static void awardMoveScore(GameState &state, bool followedSuggestion);
};

#endif 