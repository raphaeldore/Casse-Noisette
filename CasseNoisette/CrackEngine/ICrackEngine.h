#pragma once

namespace CrackEngine
{
	class ICrackEngine
	{
	public:
		virtual ~ICrackEngine() {}
		virtual void Crack() = 0;
		void setPwdFilePath(const string & _pwdFilePath);
		void setResultsFilePath(const string & _resultsFilePath);
		void setPwdHashFunction(const string & _pwdHashFunction);
		vector<string> getResults();
	protected:
		string pwdFilePath;
		string resultsFilePath;
		string pwdHashFunction;

		vector<string> results;
	};
}