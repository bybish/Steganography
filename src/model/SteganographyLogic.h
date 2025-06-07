#pragma once
#include <string>

class SteganographyLogic {
public:
    static std::string encrypt(const std::string& text, const std::string& message);
    static std::string decrypt(const std::string& encryptedText);
};