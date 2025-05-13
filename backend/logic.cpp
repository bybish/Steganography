#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>

const short CHAR_LENGTH = std::numeric_limits<unsigned char>::digits;

std::string binary_num(unsigned char byte)								
{
	std::bitset<8> bits(byte);
	return bits.to_string(); 
}

std::string binary_string(const std::string& str)						
{
	std::string buffer;
	buffer.reserve(str.size() * CHAR_LENGTH);

	for (unsigned char c : str) 
	{
		buffer += binary_num(c);
	}
	return buffer;
}

std::string encrypt(std::string& str, const std::string& msg, int idx)	// 
{
	str.erase(0, str.find_first_not_of(' '));
	str.erase(str.find_last_not_of(' ') + 1);

	for (int i = 1; i < str.size(); ++i)
	{
		if (str[i] == ' ' && str[i - 1] == ' ')
		{
			str.erase(i, 1);
			--i;
		}
	}

	int s = 0;
	for (int i = idx; i < str.size(); ++i)
	{
		if (str[i] == ' ')
			++s;
	}
	
	std::string bin_msg = binary_string(msg);

	if (s < msg.size()*CHAR_LENGTH)
		return "Error: length of your message is less then count of spaces in text";

	int k = 0;
	for (int i = idx; i < str.size() && k < msg.size() * CHAR_LENGTH; ++i)
	{
		if (str[i] == ' ')
		{
			if (bin_msg[k] == '1')
			{
				str.insert(i, " ");
				++i;
			}
			++k;
		}
	}
	
	//std::cout << "Текст с зашифрованным сообщением: ";
	return str;
}

std::string decrypt(const std::string& str, int msg_size, int idx)
{
	std::string bin_msg;
	bin_msg.reserve(msg_size*CHAR_LENGTH);

	int k = 0;
	for (int i = idx; i < str.size() - 1 && k < msg_size* CHAR_LENGTH; ++i)
	{
		if (str[i] == ' ') 
		{
			if (str[i + 1] == ' ') 
			{
				bin_msg += '1';
				++i;
			}
			else 
			{
				bin_msg += '0';
			}

			++k;
		}
	}

	std::string dec_msg;
	for (size_t i = 0; i + 7 < bin_msg.size(); i += 8) 
	{
		std::bitset<8> bits(bin_msg.substr(i, 8));
		unsigned char byte = static_cast<unsigned char>(bits.to_ulong());
		dec_msg += byte;
	}

	//std::cout << "Расшифрованное слово: ";
	return dec_msg;
}

void main()
{
	setlocale(LC_ALL, "Russian");
	return;
}