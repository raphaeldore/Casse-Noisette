#pragma once
#include "stdafx.h"

namespace CrackEngine
{
	class BruteForce : public ICrackEngine
	{
	public:
		BruteForce(const std::string & _crackingCharset);
		~BruteForce() override;
		void Crack() override;
	private:
		std::string crackingCharset;
	};

}