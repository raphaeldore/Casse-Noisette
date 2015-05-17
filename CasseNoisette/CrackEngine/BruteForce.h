#pragma once

#include "ICrackEngine.h"

namespace CrackEngine
{
	class BruteForce : public ICrackEngine
	{
	public:
		BruteForce(const int & _maxPwdLenght, const std::string& _crackingCharset = "");
		~BruteForce() override;
		void Crack() override;

		void setMaxPwdLenght(const int & _maxPwdLenght);
		void setCrackingCharset(const std::string & _crackingCharset);

	private:
		std::string Crack(const std::string & _hashedPassword) const;

		std::string crackingCharset;
		int maxPwdLenght;
	};
}