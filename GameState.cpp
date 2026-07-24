#include "GameState.h"

GameState::GameState()
    : player(), wolf(), graph(nullptr), score(0), turnNumber(1), status(GameStatus::Playing) {}

GameState::GameState(const Graph *g)
    : player(), wolf(), graph(g), score(0), turnNumber(1), status(GameStatus::Playing) {}

GameState::GameState(const GameState &other)
    : player(other.player), wolf(other.wolf), graph(other.graph),
      score(other.score), turnNumber(other.turnNumber), status(other.status) {}

GameState &GameState::operator=(const GameState &other)
{
    if (this != &other)
    {
        player = other.player;
        wolf = other.wolf;
        graph = other.graph;
        score = other.score;
        turnNumber = other.turnNumber;
        status = other.status;
    }
    return *this;
}

Player &GameState::getPlayer() { return player; }
const Player &GameState::getPlayer() const { return player; }
void GameState::setPlayer(const Player &p) { player = p; }

Wolf &GameState::getWolf() { return wolf; }
const Wolf &GameState::getWolf() const { return wolf; }
void GameState::setWolf(const Wolf &w) { wolf = w; }

const Graph *GameState::getGraph() const { return graph; }
void GameState::setGraph(const Graph *g) { graph = g; }

int GameState::getScore() const { return score; }
void GameState::setScore(int s) { score = s; }

int GameState::getTurnNumber() const { return turnNumber; }
void GameState::setTurnNumber(int turn) { turnNumber = turn; }
void GameState::nextTurn() { turnNumber++; }

GameStatus GameState::getStatus() const { return status; }
void GameState::setStatus(GameStatus s) { status = s; }
bool GameState::isGameOver() const { return status != GameStatus::Playing; }

void GameState::reset()
{
    player.reset();
    wolf.reset();
    score = 0;
    turnNumber = 1;
    status = GameStatus::Playing;
}