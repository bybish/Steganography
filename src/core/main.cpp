#include "FileManager.h"
#include <iostream>

int main() {
    FileManager manager;

    std::string content = manager.loadFile("input.txt");
    if (!content.empty()) {
        std::cout << "Содержимое файла:\n" << content << std::endl;

        // можно здесь обработать content

        manager.saveFile("output.txt", content);
        std::cout << "Сохранено в output.txt" << std::endl;
    }

    return 0;
}