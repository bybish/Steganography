#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string FileManager::loadFile(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Ошибка при открытии файла: " << filePath << std::endl;
        return "";
    }

    std::ostringstream ss;
    ss << inFile.rdbuf();
    buffer = ss.str();
    inFile.close();

    return buffer;
}

void FileManager::saveFile(const std::string& filePath, const std::string& content) {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка при сохранении в файл: " << filePath << std::endl;
        return;
    }

    outFile << content;
    outFile.close();
}

std::string FileManager::getBuffer() const {
    return buffer;
}
