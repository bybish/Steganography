#include <iostream>
#include <string>
#include <unordered_map>
#include <bitset>
#include <locale>
#include <clocale>

const short CHAR_LENGTH = 16;

const std::unordered_map<wchar_t, wchar_t> ru_to_en_16 =
{
	{L'А', L'A'}, {L'а', L'a'}, {L'В', L'B'}, {L'Е', L'E'}, {L'е', L'e'}, {L'К', L'K'},
	{L'М', L'M'}, {L'Н', L'H'}, {L'О', L'O'}, {L'о', L'o'}, {L'Р', L'P'}, {L'р', L'p'},
	{L'С', L'C'}, {L'с', L'c'}, {L'Т', L'T'}, {L'у', L'y'}, {L'Х', L'X'}, {L'х', L'x'}
};


const std::unordered_map<wchar_t, wchar_t> en_to_ru_16 = 
{
	{L'A', L'А'}, {L'a', L'а'}, {L'B', L'В'}, {L'E', L'Е'}, {L'e', L'е'}, {L'K', L'К'},
	{L'M', L'М'}, {L'H', L'Н'}, {L'O', L'О'}, {L'o', L'о'}, {L'P', L'Р'}, {L'p', L'р'},
	{L'C', L'С'}, {L'c', L'с'}, {L'T', L'Т'}, {L'y', L'у'}, {L'X', L'Х'}, {L'x', L'х'}
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

std::wstring encrypt(std::wstring& str, const std::wstring& msg)
{
	std::string bin_msg;
	bin_msg.reserve(msg.size() * CHAR_LENGTH);

	bin_msg = binary_string(msg);

	if (eq_symbols_count(str) < bin_msg.size())
		return L"Длина двоичного представления шифруемого сообщения больше количества символов для шифрования в тексте.";

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

std::wstring decrypt(std::wstring& str)
{
	std::string bin_msg;

	for (int i = 0; i < str.size(); ++i)
	{
		wchar_t current = str[i];

		if (ru_to_en_16.count(current))
		{
			bin_msg += '1';
		}
		else if (en_to_ru_16.count(current))
		{
			bin_msg += '0';
		}
	}

	std::wstring decrypted;

	for (size_t i = 0; i + CHAR_LENGTH <= str.size(); i += CHAR_LENGTH)
	{
		std::bitset<CHAR_LENGTH> bits(bin_msg.substr(i, CHAR_LENGTH));
		wchar_t ch = static_cast<wchar_t>(bits.to_ulong());
		if (ch != 0)             
			decrypted += ch;
	}

	return decrypted;
}

int main()
{
	std::locale::global(std::locale(""));
	std::wcin.imbue(std::locale());
	std::wcout.imbue(std::locale());
	return 0;
}

