#include "ScoreManager.h"

void ScoreManager::awardFollowDijkstra(GameState& state) {
    state.setScore(state.getScore() + SFollowDijkstra);
}

void ScoreManager::awardValidMove(GameState& state) {
    state.setScore(state.getScore() + SValidMove);
}

void ScoreManager::applyUndoPenalty(GameState& state) {
    state.setScore(state.getScore() + SUndo);
}

void ScoreManager::awardWinBonus(GameState& state) {
    state.setScore(state.getScore() + SWin);
}

void ScoreManager::awardMoveScore(GameState& state, bool followedSuggestion) {
    if (followedSuggestion) {
        awardFollowDijkstra(state);
    } else {
        awardValidMove(state);
    }
}