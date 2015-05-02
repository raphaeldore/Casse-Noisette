#include "stdafx.h"
#include "CharsetBuilder.h"

using namespace CrackEngine;

/* Les différents groupes de caractères que nous supportons */
namespace Charsets
{
	const string loweralpha = "abcdefghijklmnopqrstuvwxyz";
	const string upperalpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const string numeric = "0123456789";
	const string space = " ";
	const string special = "!@#$%^&*()-_+=";
}

CharsetBuilder::CharsetBuilder()
{
	enableLowerAlpha(); // Par défaut
	upperalpha = false;
	numeric = false;
	space = false;
	special = false;
}

CharsetBuilder::CharsetBuilder(const bool _loweralpha, const bool _upperalpha, const bool _numeric, const bool _space, const bool _special)
{
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

string CharsetBuilder::BuildCharset()
{
	string generatedCharset = "";

	if (loweralpha) generatedCharset.append(Charsets::loweralpha);
	if (upperalpha) generatedCharset.append(Charsets::upperalpha);
	if (numeric) generatedCharset.append(Charsets::numeric);
	if (space) generatedCharset.append(Charsets::space);
	if (special) generatedCharset.append(Charsets::special);

	return generatedCharset;
}