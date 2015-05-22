#include "stdafx.h"
#include "SHA512.h"
#include <openssl/sha.h>

using namespace CustomCrypto;
using namespace std;

SHA512::~SHA512()
{
}

string SHA512::hash(const string & _stringToHash)
{
	unsigned char hash_digest[SHA512_DIGEST_LENGTH];

	SHA512_CTX context;
	SHA512_Init(&context);
	SHA512_Update(&context, _stringToHash.c_str(), _stringToHash.size());
	SHA512_Final(hash_digest, &context);

	char charBuffer[SHA512_DIGEST_LENGTH * 2 + 1];

	// On convertit les charactères en hexadecimal 
	for (unsigned int i = 0; i < SHA512_DIGEST_LENGTH; i++)
	{
		sprintf(&charBuffer[i * 2], "%02x", hash_digest[i]);
	}

	return string(charBuffer);
}