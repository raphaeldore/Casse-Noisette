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
		static void Register(const string & _hashName, unique_ptr<IHash> _hashFunction);
		IHash * CreateHashAlgorithm(const string & _hashName) const;

	private:
		// On veut empêcher les copies.
		HashFactory(const HashFactory &) { }
		// On renvoit toujours une référence vers l'instance originale
		HashFactory &operator=(const HashFactory &) { return *this; }

		static map<string, unique_ptr<IHash>> hashAlgorithms_map;
	};
}