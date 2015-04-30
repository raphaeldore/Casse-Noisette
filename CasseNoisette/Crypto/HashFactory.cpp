#include "stdafx.h"
#include "HashFactory.h"

using namespace CustomCrypto;

map<string, unique_ptr<IHash>> HashFactory::hashAlgorithms_map;

HashFactory::HashFactory()
{
	// Les algorithmes de hachage qu'on supporte pour l'instant.
	// C'est très facile d'en ajouter.
	Register("MD5", make_unique<MD5>());
	Register("SHA-1", make_unique<SHA1>());
	Register("SHA-256", make_unique<SHA256>());
}

HashFactory::~HashFactory()
{
}

HashFactory * HashFactory::GetHashFactory()
{
	static unique_ptr<HashFactory> factoryInstance = make_unique<HashFactory>();
	return factoryInstance.get();
}

void HashFactory::Register(const string _hashName, unique_ptr<IHash> _hashFunction)
{
	if (hashAlgorithms_map.find(_hashName) == hashAlgorithms_map.end())
	{
		hashAlgorithms_map[_hashName] = move(_hashFunction);
	}
}

IHash * HashFactory::CreateHashAlgorithm(const string& _hashName) const
{
	if (hashAlgorithms_map.find(_hashName) == hashAlgorithms_map.end())
		throw invalid_argument(string(__FUNCTION__) + ": unknown hash algorithm");

	return hashAlgorithms_map.at(_hashName).get();
}