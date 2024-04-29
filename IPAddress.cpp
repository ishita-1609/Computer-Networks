#include <stdio.h>
//#include <tchar.h>
#include <stdint.h>
#include "IPAddress.h"
#include <sstream>

IPAddress::IPAddress(std::string s_address)
	: value(0)
{
	std::stringstream ss(s_address);
	std::string token;
	char delim = '.';
	int i = 3;
	// Turn every split part into an int, then sum.
	while (std::getline(ss, token, delim)) {
		int field_value = std::stoi(token) << 8*i;
		i--;
		this->value += field_value;
	}
}

std::string IPAddress::to_string() {
	std::string str = "";
	for (int i = 0; i < 4; i++) {
		int bitmask = 0xFF << (8*(3 - i));
		int field_value = (this->value & bitmask)>>(8 * (3 - i));
		str += std::to_string(field_value);
		if (i < 3) {
			str += ".";
		}
	}
	return str;
}

uint32_t IPAddress::get_value() {
	return this->value;
}

int IPAddress::get_mask() {
	int mask = 0xFFFFFFFF;
	int i = 32;
	while (this->value != mask) {
		i--;
		mask = mask << 1;
		if (mask == 0) {
			return 0;
		}
	}
	return i;
}
