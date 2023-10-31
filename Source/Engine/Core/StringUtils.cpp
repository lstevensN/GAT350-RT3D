#include "StringUtils.h"

namespace nc
{
	std::string StringUtils::ToUpper(std::string input)
	{
		std::string output;

		// converts all char's in input to lowercase characters
		for (char c : input) { output += toupper(c); }

		return output;
	}

	std::string StringUtils::ToLower(std::string input)
	{
		std::string output;

		// converts all char's in input to uppercase characters
		for (char c : input) { output += tolower(c); }

		return output;
	}

	bool StringUtils::IsEqualIgnoreCase(std::string string1, std::string string2)
	{
		// converts strings to lowercase, then compares them
		if (StringUtils::ToLower(string1) == StringUtils::ToLower(string2)) return true;
		else return false;
	}

	std::string StringUtils::CreateUnique(const std::string& str)
	{
		// Thanks Professor
		static uint32_t unique = 0;

		return str + std::to_string(unique++);
	}
}
