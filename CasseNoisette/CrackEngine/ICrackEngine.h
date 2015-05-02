#pragma once

namespace CrackEngine
{
	class ICrackEngine
	{
	public:
		virtual ~ICrackEngine() {}
		//virtual void Crack() = 0;
		virtual void Crack();
		void setPwdFilePath(const string & _pwdFilePath);
		void setResultsFilePath(const string & _resultsFilePath);
		void setPwdHashFunction(const string & _pwdHashFunction);
	private:
		string pwdFilePath;
		string resultsFilePath;
		string pwdHashFunction;
	};
}