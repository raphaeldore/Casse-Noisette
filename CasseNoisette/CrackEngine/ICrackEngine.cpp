#include "stdafx.h"
#include "ICrackEngine.h"

using namespace CrackEngine;

void ICrackEngine::setHashedPasswords(const vector<string>& _hashedPasswords)
{
	hashedPasswords = _hashedPasswords;
}

void ICrackEngine::setResultsFilePath(const string& _resultsFilePath)
{
	resultsFilePath = _resultsFilePath;
}

void ICrackEngine::setPwdHashFunction(const string& _pwdHashFunction)
{
	hashAlgorithm = CustomCrypto::HashFactory::GetHashFactory()->CreateHashAlgorithm(_pwdHashFunction);
}

vector<string> ICrackEngine::getResults()
{
	return results;
}