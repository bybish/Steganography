#ifndef STEGANOGRAPHY_LOGIC_H
#define STEGANOGRAPHY_LOGIC_H

#include <QString>

class SteganographyLogic {
public:
    static QString encode(const QString& input);
    static QString decode(const QString& input);
};

#endif