#include "stdafx.h"
#include "ICrackEngine.h"

using namespace CrackEngine;

void ICrackEngine::Crack()
{
}

void ICrackEngine::setPwdFilePath(const string& _pwdFilePath)
{
	pwdFilePath = _pwdFilePath;
}

void ICrackEngine::setResultsFilePath(const string& _resultsFilePath)
{
	resultsFilePath = _resultsFilePath;
}

void ICrackEngine::setPwdHashFunction(const string& _pwdHashFunction)
{
	pwdHashFunction = _pwdHashFunction;
}