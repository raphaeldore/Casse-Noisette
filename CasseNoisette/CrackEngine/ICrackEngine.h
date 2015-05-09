#pragma once

namespace CrackEngine
{
	class ICrackEngine
	{
	public:
		virtual ~ICrackEngine() {}
		virtual void Crack() = 0;
		void setHashedPasswords(const multimap<string, string> & _hashedPasswords);
		void setResultsFilePath(const string & _resultsFilePath);
		void setPwdHashFunction(const string & _pwdHashFunction);
		vector<tuple<string, string, string>> getResults();
	protected:
		typedef vector<tuple<string, string, string>> StringTupleVector;

		CustomCrypto::IHash * hashAlgorithm;
		string resultsFilePath;
		multimap<string, string> hashedPasswords;
		StringTupleVector results;
	};
}