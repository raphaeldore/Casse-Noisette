#pragma once
#include "stdafx.h"

namespace CustomCrypto
{
	class MD5 : public IHash
	{
	public:
		~MD5() override;
		string hash(const string _stringToHash) override;

	private:

		void F(int x, int y, int z);

		int count[2];
		int state[4];
	};
}