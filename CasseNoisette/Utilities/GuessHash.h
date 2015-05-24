#pragma once
#include <map>


namespace Utilities {
	class GuessHash
	{
	public:

		static bool Guess(const std::string & _sampleHash, std::string & _outGuessedHash);

	private:
		static std::map<std::string, std::string>  hashFunction_regex_map;

	};
}