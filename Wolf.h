#ifndef WOLF_H
#define WOLF_H

#include <string>

class Wolf {
private:
    std::string position;

public:
    Wolf();
    explicit Wolf(const std::string& startPos);

    std::string getPosition() const;
    void setPosition(const std::string& pos);

    void reset(const std::string& startPos = "");
};

#endif