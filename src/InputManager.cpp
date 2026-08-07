#include "InputManager.h"

#include <iostream>
#include <algorithm>
#include <cctype>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

std::string InputManager::trim(const std::string& text) {
    size_t start = text.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(start, end - start + 1);
}

std::string InputManager::toUpper(const std::string& text) {
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    return result;
}

int InputManager::readMenuChoice(int min, int max) {
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        line = trim(line);

        try {
            size_t consumed = 0;
            int value = std::stoi(line, &consumed);

            if (consumed == line.size() && value >= min && value <= max) {
                return value;
            }
        } catch (...) {

        }

        std::cout << "  Please enter a number between " << min << " and " << max << ": ";
    }
}

std::string InputManager::readString(bool echo) {
    if (echo) {
        std::string line;
        std::getline(std::cin, line);
        return trim(line);
    }

    std::string password;

#ifdef _WIN32
    char ch = static_cast<char>(_getch());
    while (ch != '\r' && ch != '\n') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        } else {
            password.push_back(ch);
            std::cout << '*';
        }
        ch = static_cast<char>(_getch());
    }
    std::cout << std::endl;
#else
    termios oldSettings{};
    termios newSettings{};

    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

    std::getline(std::cin, password);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
    std::cout << std::endl;
#endif

    return trim(password);
}

std::string InputManager::parseMoveInput(const std::string& input,const std::vector<std::string>& validMoves, const std::string& suggestedNext, bool canUndo,bool& valid) {
    valid = false;
    std::string normalized = toUpper(trim(input));

    if (normalized.empty()) {
        return "";
    }

    if (normalized == "U") {
        if (canUndo) {
            valid = true;
            return "U";
        }
        return "";
    }

    if (normalized == "D") {
        if (!suggestedNext.empty()) {
            valid = true;
            return suggestedNext;
        }
        return "";
    }

    for (const std::string& vertex : validMoves) {
        if (toUpper(vertex) == normalized) {
            valid = true;
            return vertex;
        }
    }

    return "";
}
