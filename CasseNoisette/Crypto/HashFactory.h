#pragma once
#include "stdafx.h"

using namespace std;

namespace CustomCrypto
{
	class IHash;

	class HashFactory
	{
	public:
		HashFactory();
		virtual ~HashFactory();

		static HashFactory * GetHashFactory();

		static void Register(const string _hashName, unique_ptr<IHash> _hashFunction);
		IHash * CreateHashAlgorithm(const string & _hashName) const;

	private:
		static map<string, unique_ptr<IHash>> hashFunctions_map;
	};
}