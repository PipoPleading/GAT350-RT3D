#include "StringUtils.h"

namespace nc
{
	std::string ToUpper(const std::string& str)
	{
		std::string result = str;
		for (char& c : result) c = std::toupper(c);

		return result;
	}

	std::string ToLower(const std::string& str)
	{
		std::string result = str;
		for (char& c : result) c = std::tolower(c);

		return result;
	}

	bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2)
	{
		if (str1.size() != str2.size()) return false;

		return std::equal(str1.begin(), str1.end(), str2.begin(), str2.end(), [](char a, char b) 
			{
				return std::tolower(a) == std::tolower(b);
			});
	}

	std::string CreateUnique(const std::string& str)
	{
		static uint32_t unique = 0;

		return str + std::to_string(unique++);
	}
}