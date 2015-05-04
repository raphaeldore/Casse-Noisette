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
		removeDuplicateCharacters(generatedCharset);
	}

	return generatedCharset;
}

void CharsetBuilder::removeDuplicateCharacters(string& _generatedCharset)
{
	sort(_generatedCharset.begin(), _generatedCharset.end());
	_generatedCharset.erase(unique(_generatedCharset.begin(), _generatedCharset.end()));
}