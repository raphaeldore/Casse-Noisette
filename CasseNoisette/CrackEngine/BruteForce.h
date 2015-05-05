#pragma once
#include "ICrackEngine.h"

namespace CrackEngine
{
	class BruteForce : public ICrackEngine
	{
	public:
		BruteForce(const int & _maxPwdLenght, const string& _crackingCharset = "");
		~BruteForce() override;
		void Crack() override;

		void setMaxPwdLenght(const int & _maxPwdLenght);
		void setCrackingCharset(const string & _crackingCharset);

	private:
		string Crack(const string & _hashedPassword) const;

		string crackingCharset;
		int maxPwdLenght;
	};
}