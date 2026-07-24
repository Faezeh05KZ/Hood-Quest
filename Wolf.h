#ifndef WOLF_H
#define WOLF_H

class Wolf {
private:
    int position;

public:
    Wolf();
    explicit Wolf(int startPos);

    int getPosition() const;
    void setPosition(int pos);

    void reset(int startPos = 0);
};

#endif 