#pragma once
#include <string>

class IPAddress
{
public:
	IPAddress(std::string s_address);
	std::string to_string();
	uint32_t get_value();
	int get_mask();
private:
	uint32_t value;
};
