#pragma once
#include "stdafx.h"

namespace CustomCrypto
{
	class SHA1 : public IHash
	{
	public:
		~SHA1() override;
		string hash(const string & _stringToHash) override;
	};
}