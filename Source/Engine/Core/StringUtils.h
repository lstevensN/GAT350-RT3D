#pragma once
#include <string>

namespace nc
{
	class StringUtils
	{
	public:
		static std::string ToUpper(std::string input);
		static std::string ToLower(std::string input);

		static bool IsEqualIgnoreCase(std::string string1, std::string string2);
		static std::string CreateUnique(const std::string& str);
	};
}
