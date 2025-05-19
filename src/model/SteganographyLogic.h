#pragma once

#include <string>

class SteganographyLogic {
public:
    static std::string encrypt(const std::string& text, const std::string& message, int index = 0);
    static std::string decrypt(const std::string& text, int messageSize, int index = 0);

private:
    static constexpr short CHAR_LENGTH = 8;

    static std::string byteToBinary(unsigned char byte);
    static std::string stringToBinary(const std::string& str);
};