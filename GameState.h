#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Player.h"
#include "Wolf.h"
#include "Graph.h"

enum class GameStatus { Playing, Won, Lost };

class GameState {
private:
    Player player;
    Wolf wolf;
    const Graph* graph; 
    int score;
    int turnNumber;
    GameStatus status;

public:
    GameState();
    GameState(const Player& p, const Wolf& w, const Graph* g, int initialScore = 0);

    GameState(const GameState& other);

    GameState& operator=(const GameState& other);

    void reset();
    void nextTurn();
    bool isGameOver() const;

    Player& getPlayer();
    const Player& getPlayer() const;
    void setPlayer(const Player& p);

    Wolf& getWolf();
    const Wolf& getWolf() const;
    void setWolf(const Wolf& w);

    const Graph* getGraph() const;
    void setGraph(const Graph* g);

    int getScore() const;
    void setScore(int s);

    int getTurnNumber() const;
    void setTurnNumber(int turn);

    GameStatus getStatus() const;
    void setStatus(GameStatus s);
};

#endif 