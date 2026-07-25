#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string position; 

public:
    Player();
    explicit Player(const std::string& startPos);

    std::string getPosition() const;
    void setPosition(const std::string& pos);

    void reset(const std::string& startPos = "");
};

#endif