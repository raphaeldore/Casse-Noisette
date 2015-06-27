#include "stdafx.h"
#include "StringUtilities.h"

using namespace Utilities;

std::string StringUtilities::basicToLower(const std::string& _string)
{
	std::string loweredString;
	for (auto c : _string)
	{
		loweredString += tolower(c);
	}

	return loweredString;
}