#pragma once

namespace CrackEngine
{
	class BruteForce : public ICrackEngine
	{
	public:
		BruteForce(const int & _maxPwdLenght);
		BruteForce(const string & _crackingCharset, const int & _maxPwdLenght);
		~BruteForce() override;
		void Crack() override;

		void setMaxPwdLenght(const int & _maxPwdLenght);
		void setCrackingCharset(const string & _crackingCharset);
	private:
		string crackingCharset;
		int maxPwdLenght;
	};

}