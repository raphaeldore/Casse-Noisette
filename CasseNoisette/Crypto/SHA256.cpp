#include "stdafx.h"
#include "SHA256.h"

using namespace CustomCrypto;
using namespace std;

SHA256::~SHA256()
{
}

string SHA256::hash(const string & _stringToHash)
{
	return _stringToHash;
}