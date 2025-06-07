#include "SteganographyLogic.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <bitset>
#include <locale>
#include <clocale>
#include <codecvt>

// Конвертеры между string и wstring
static std::wstring string_to_wstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

static std::string wstring_to_string(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

const short CHAR_LENGTH = 16;

// Мапы для замены символов (используем wchar_t)
static const std::unordered_map<wchar_t, wchar_t> ru_to_en_16 = {
    {L'А', L'A'}, {L'а', L'a'}, {L'В', L'B'}, {L'Е', L'E'}, {L'е', L'e'}, {L'К', L'K'},
    {L'М', L'M'}, {L'Н', L'H'}, {L'О', L'O'}, {L'о', L'o'}, {L'Р', L'P'}, {L'р', L'p'},
    {L'С', L'C'}, {L'с', L'c'}, {L'Т', L'T'}, {L'у', L'y'}, {L'Х', L'X'}, {L'х', L'x'}
};

static const std::unordered_map<wchar_t, wchar_t> en_to_ru_16 = {
    {L'A', L'А'}, {L'a', L'а'}, {L'B', L'В'}, {L'E', L'Е'}, {L'e', L'е'}, {L'K', L'К'},
    {L'M', L'М'}, {L'H', L'Н'}, {L'O', L'О'}, {L'o', L'о'}, {L'P', L'Р'}, {L'p', L'р'},
    {L'C', L'С'}, {L'c', L'с'}, {L'T', L'Т'}, {L'y', L'у'}, {L'X', L'Х'}, {L'x', L'х'}
};

// Вспомогательные функции (работают с wstring)
static std::string binary_num(wchar_t value) {
    std::bitset<16> bits(value);
    return bits.to_string();
}

static std::string binary_string(const std::wstring& str) {
    std::string bin_str;
    bin_str.reserve(str.size() * CHAR_LENGTH);

    for (wchar_t c : str) {
        bin_str += binary_num(c);
    }
    return bin_str;
}

static std::wstring encrypt_impl(std::wstring str, const std::wstring& msg) {
    std::string bin_msg = binary_string(msg);

    for (int i = 0, k = 0; i < str.size() && k < bin_msg.size(); ++i) {
        wchar_t current = str[i];
        bool found = false;
        wchar_t ru = 0, en = 0;

        auto it_ru = ru_to_en_16.find(current);
        if (it_ru != ru_to_en_16.end()) {
            ru = it_ru->first;
            en = it_ru->second;
            found = true;
        }
        else {
            auto it_en = en_to_ru_16.find(current);
            if (it_en != en_to_ru_16.end()) {
                en = it_en->first;
                ru = it_en->second;
                found = true;
            }
        }

        if (found) {
            str[i] = (bin_msg[k] == '1') ? ru : en;
            ++k;
        }
    }

    return str;
}

static std::wstring decrypt_impl(const std::wstring& str) {
    std::string bin_msg;

    for (wchar_t current : str) {
        if (ru_to_en_16.count(current)) {
            bin_msg += '1';
        }
        else if (en_to_ru_16.count(current)) {
            bin_msg += '0';
        }
    }

    std::wstring decrypted;
    for (size_t i = 0; i + CHAR_LENGTH <= bin_msg.size(); i += CHAR_LENGTH) {
        std::bitset<CHAR_LENGTH> bits(bin_msg.substr(i, CHAR_LENGTH));
        wchar_t ch = static_cast<wchar_t>(bits.to_ulong());
        if (ch != 0) {
            decrypted += ch;
        }
    }

    return decrypted;
}

std::string SteganographyLogic::encrypt(const std::string& text, const std::string& message) {
    std::wstring wtext = string_to_wstring(text);
    std::wstring wmsg = string_to_wstring(message);
    std::wstring result = encrypt_impl(wtext, wmsg);
    return wstring_to_string(result);
}

std::string SteganographyLogic::decrypt(const std::string& encryptedText) {
    std::wstring wencrypted = string_to_wstring(encryptedText);
    std::wstring result = decrypt_impl(wencrypted);
    return wstring_to_string(result);
}