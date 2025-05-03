#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager {
private:
    std::string buffer;

public:
    std::string loadFile(const std::string& filePath);
    void saveFile(const std::string& filePath, const std::string& content);
    std::string getBuffer() const;
};

#endif