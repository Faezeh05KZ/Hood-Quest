#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <string>
#include <vector>


class InputManager {
public:
    InputManager() = delete;
    static int readMenuChoice(int min, int max);

    static std::string readString(bool echo = true);

    static std::string parseMoveInput(const std::string& input,const std::vector<std::string>& validMoves,const std::string& suggestedNext,bool canUndo,bool& valid);

private:
    static std::string trim(const std::string& text);
    static std::string toUpper(const std::string& text);
};

#endif
