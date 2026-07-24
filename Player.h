#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    int position; 

public:
    Player();
    explicit Player(int startPos);

    int getPosition() const;
    void setPosition(int pos);

    void reset(int startPos = 0);
};

#endif