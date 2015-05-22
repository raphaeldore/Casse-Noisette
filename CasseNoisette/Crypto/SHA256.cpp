#include "stdafx.h"
#include "SHA256.h"
#include <openssl/sha.h>

using namespace CustomCrypto;
using namespace std;

SHA256::~SHA256()
{
}

string SHA256::hash(const string & _stringToHash)
{
	unsigned char hash_digest[SHA256_DIGEST_LENGTH];

	SHA256_CTX context;
	SHA256_Init(&context);
	SHA256_Update(&context, _stringToHash.c_str(), _stringToHash.size());
	SHA256_Final(hash_digest, &context);

	char charBuffer[SHA256_DIGEST_LENGTH * 2 + 1];

	// On convertit les charactères en hexadecimal 
	for (unsigned int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(&charBuffer[i * 2], "%02x", hash_digest[i]);
	}

	return string(charBuffer);
}