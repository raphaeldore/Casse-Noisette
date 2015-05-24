#include "stdafx.h"
#include "GuessHash.h"

#include <regex>

using namespace Utilities;
using namespace std;

map<string, string> GuessHash::hashFunction_regex_map = { make_pair("MD5", "^[a-f0-9]{32}$"),
                                                          make_pair("SHA-1", "^[a-f0-9]{40}$"),
												          make_pair("SHA-256", "^[a-f0-9]{64}$"),
												          make_pair("SHA-512", "^[a-f0-9]{128}$") };

bool GuessHash::Guess(const std::string & _sampleHash, std::string & _outGuessedHash)
{
	for (const auto hashRegex : hashFunction_regex_map)
	{
		if (regex_match(_sampleHash, regex(hashRegex.second)))
		{
			_outGuessedHash = hashRegex.first;
			return true;
		}
	}

	return false;
}