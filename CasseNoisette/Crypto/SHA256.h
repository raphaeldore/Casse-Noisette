#pragma once
#include "stdafx.h"

namespace CustomCrypto
{
	class SHA256 : public IHash
	{
	public:
		~SHA256() override;
		string hash(const string _stringToHash) override;
	};
}