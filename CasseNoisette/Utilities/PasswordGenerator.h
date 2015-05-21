#pragma once

namespace Utilities
{
	class PasswordGenerator
	{
	public:
		static std::string GeneratePassword(const std::string& _charset, const unsigned int& _lenght);
	private:
		static char GenerateRandomCharacter(const std::string& _charset);
	};
}