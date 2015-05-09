#include "stdafx.h"
#include "CharsetBuilder.h"
#include <algorithm>

using namespace CrackEngine;

CharsetBuilder::CharsetBuilder() : customCharset("")
{
	loweralpha = false;
	upperalpha = false;
	numeric = false;
	space = false;
	special = false;
}

CharsetBuilder::CharsetBuilder(const bool _loweralpha, const bool _upperalpha, const bool _numeric, const bool _space, const bool _special, const string & _customCharset)
{
	customCharset = _customCharset;
	loweralpha = _loweralpha;
	upperalpha = _upperalpha;
	numeric = _numeric;
	space = _space;
	special = _special;
}

void CharsetBuilder::enableLowerAlpha()
{
	loweralpha = true;
}

void CharsetBuilder::enableUpperAlpha()
{
	upperalpha = true;
}

void CharsetBuilder::enableNumeric()
{
	numeric = true;
}

void CharsetBuilder::enableSpace()
{
	space = true;
}

void CharsetBuilder::enableSpecial()
{
	special = true;
}

void CharsetBuilder::addCustomCharset(const string& _customCharset)
{
	customCharset = _customCharset;
}

string CharsetBuilder::BuildCharset()
{
	string generatedCharset = "";

	if (loweralpha) generatedCharset.append(Charsets::loweralpha);
	if (upperalpha) generatedCharset.append(Charsets::upperalpha);
	if (numeric) generatedCharset.append(Charsets::numeric);
	if (space) generatedCharset.append(Charsets::space);
	if (special) generatedCharset.append(Charsets::special);

	if (!customCharset.empty()) {
		generatedCharset.append(customCharset);
		// Au cas où l'utilisateur ajoute un charactère qui existe deja.
		generatedCharset = removeDuplicateCharacters(generatedCharset);
	}

	return generatedCharset;
}

string CharsetBuilder::removeDuplicateCharacters(const string& _generatedCharset) const
{
	string generatedCharset = _generatedCharset;
	sort(generatedCharset.begin(), generatedCharset.end());

	string cleanedCharset;

	for (auto it = generatedCharset.begin(); it < generatedCharset.end(); ++it)
	{
		auto currentChar = (*it);

		// Si le prochain caractère est le même, on l'ignore.
		while (next(it) != generatedCharset.end() && *next(it) == currentChar)
		{
			++it;
		}

		cleanedCharset += currentChar;
	}

	return cleanedCharset;
}