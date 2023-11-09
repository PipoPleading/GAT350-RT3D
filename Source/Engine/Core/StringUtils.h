#pragma once
#include <string>

namespace nc
{
	std::string ToUpper(const std::string& str);
	std::string ToLower(const std::string& str);
	bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2);
	std::string CreateUnique(const std::string& str);
}