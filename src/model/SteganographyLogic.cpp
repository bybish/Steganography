#include "SteganographyLogic.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <bitset>
#include <locale>
#include <clocale>
#include <codecvt>


static std::wstring string_to_wstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

static std::string wstring_to_string(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

const short CHAR_LENGTH = 16;

const std::unordered_map<wchar_t, wchar_t> ru_to_en_16 =
{
	{L'À', L'A'}, {L'à', L'a'}, {L'Â', L'B'}, {L'Å', L'E'}, {L'å', L'e'}, {L'Ê', L'K'},
	{L'Ì', L'M'}, {L'Í', L'H'}, {L'Î', L'O'}, {L'î', L'o'}, {L'Ð', L'P'}, {L'ð', L'p'},
	{L'Ñ', L'C'}, {L'ñ', L'c'}, {L'Ò', L'T'}, {L'ó', L'y'}, {L'Õ', L'X'}, {L'õ', L'x'}
};


const std::unordered_map<wchar_t, wchar_t> en_to_ru_16 = 
{
	{L'A', L'À'}, {L'a', L'à'}, {L'B', L'Â'}, {L'E', L'Å'}, {L'e', L'å'}, {L'K', L'Ê'},
	{L'M', L'Ì'}, {L'H', L'Í'}, {L'O', L'Î'}, {L'o', L'î'}, {L'P', L'Ð'}, {L'p', L'ð'},
	{L'C', L'Ñ'}, {L'c', L'ñ'}, {L'T', L'Ò'}, {L'y', L'ó'}, {L'X', L'Õ'}, {L'x', L'õ'}
};

std::string binary_num(wchar_t value)
{
	std::bitset<16> bits(value);
	return bits.to_string();
}

std::string binary_string(const std::wstring& str)
{
	std::string bin_str;
	bin_str.reserve(str.size() * CHAR_LENGTH);

	for (wchar_t c : str)
	{
		bin_str += binary_num(c);
	}
	return bin_str;
}

long long eq_symbols_count(const std::wstring& str)
{
	long long k = 0;
	for (int i = 0; i < str.size(); ++i)
	{
		wchar_t current = str[i];

		auto it_ru = ru_to_en_16.find(current);
		auto it_en = en_to_ru_16.find(current);
		if ((it_ru != ru_to_en_16.end()) || (it_en != en_to_ru_16.end()))
			++k;
	}
	
	return k;
}

std::wstring encrypt_impl(std::wstring& str, const std::wstring& msg)
{
	std::string bin_msg;
	bin_msg.reserve(msg.size() * CHAR_LENGTH);

	bin_msg = binary_string(msg);

	if (eq_symbols_count(str) < bin_msg.size())
		throw std::runtime_error("Длина двоичного представления шифруемого сообщения больше количества символов для шифрования в тексте.");

	for (int i = 0, k = 0; i < str.size() && k < bin_msg.size(); ++i)
	{
		wchar_t current = str[i];
		wchar_t ru = 0, en = 0;
		bool found = false;

		auto it_ru = ru_to_en_16.find(current);
		if (it_ru != ru_to_en_16.end()) 
		{
			ru = it_ru->first;
			en = it_ru->second;
			found = true;
		}
		else 
		{
			auto it_en = en_to_ru_16.find(current);
			if (it_en != en_to_ru_16.end()) 
			{
				en = it_en->first;
				ru = it_en->second;
				found = true;
			}
		}

		if (found)
		{
			wchar_t old_char = str[i];

			if (bin_msg[k] == '1')
				str[i] = ru;
			else
				str[i] = en; 

			++k;
		}
	}

	return str;
}

std::wstring decrypt_impl(const std::wstring& str) {
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
        if (ch != 0) 
            decrypted += ch;
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