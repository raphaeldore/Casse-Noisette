#include "stdafx.h"
#include "SHA1.h"
#include <openssl/sha.h>

using namespace CustomCrypto;
using namespace std;

SHA1::~SHA1()
{
}

string SHA1::hash(const string & _stringToHash)
{
	unsigned char hash_digest[SHA_DIGEST_LENGTH];

	SHA_CTX context;
	SHA1_Init(&context);
	SHA1_Update(&context, _stringToHash.c_str(), _stringToHash.size());
	SHA1_Final(hash_digest, &context);

	char charBuffer[SHA_DIGEST_LENGTH * 2 + 1];

	// On convertit les charactères en hexadecimal 
	for (unsigned int i = 0; i < SHA_DIGEST_LENGTH; i++)
	{
		sprintf(&charBuffer[i * 2], "%02x", hash_digest[i]);
	}

	return string(charBuffer);

}