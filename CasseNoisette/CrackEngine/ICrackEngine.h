#pragma once

namespace CrackEngine
{
	class ICrackEngine
	{
	public:
		virtual ~ICrackEngine() {}
		virtual void Crack() = 0;
		void setHashedPasswords(const vector<tuple<string,string,string>> & _hashedPasswords);
		void setResultsFilePath(const string & _resultsFilePath);
		void setPwdHashFunction(const string & _pwdHashFunction);
		vector<string> getResults();
	protected:
		CustomCrypto::IHash * hashAlgorithm;
		string resultsFilePath;
		vector<tuple<string,string,string>> hashedPasswords;
		vector<string> results;
	};
}