#pragma once
#include "stdafx.h"

using namespace std;

namespace CustomCrypto
{
	class IHash
	{
	public :
		virtual ~IHash();

		virtual string hash(const string & _stringToHash) = 0;
	};
}