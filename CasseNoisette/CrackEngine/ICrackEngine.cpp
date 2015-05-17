#include "stdafx.h"
#include "ICrackEngine.h"
#include "../Crypto/HashFactory.h"

using namespace CrackEngine;
using namespace std;

void ICrackEngine::cancelCrack()
{
	running = false;
}

void ICrackEngine::setHashedPasswords(const multimap<string, string> & _hashedPasswords)
{
	hashedPasswords = _hashedPasswords;
}

void ICrackEngine::setPwdHashFunction(const string& _pwdHashFunction)
{
	hashAlgorithm = CustomCrypto::HashFactory::GetHashFactory()->CreateHashAlgorithm(_pwdHashFunction);
}

vector<tuple<string, string, string>> ICrackEngine::getResults()
{
	return results;
}