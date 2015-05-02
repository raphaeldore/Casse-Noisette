#pragma once

namespace CrackEngine
{
	class ICrackEngine
	{
	public:
		virtual ~ICrackEngine() {}
		virtual void Crack() = 0;
		virtual void setPwdFilePath(const string & _pwdFilePath);
		virtual void setResultsFilePath(const string & _resultsFilePath);
		virtual void setPwdHashFunction(const string & _pwdHashFunction);
	protected:
		string pwdFilePath;
		string resultsFilePath;
		string pwdHashFunction;
	};
}