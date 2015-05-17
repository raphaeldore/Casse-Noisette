#pragma once

namespace CustomCrypto
{
	class IHash;

	class HashFactory
	{
	public:
		HashFactory();
		virtual ~HashFactory();

		static HashFactory * GetHashFactory();
		static void Register(const std::string & _hashName, std::unique_ptr<IHash> _hashFunction);
		IHash * CreateHashAlgorithm(const std::string & _hashName) const;

	private:
		// On veut empêcher les copies.
		HashFactory(const HashFactory &) { }
		// On renvoit toujours une référence vers l'instance originale
		HashFactory &operator=(const HashFactory &) { return *this; }

		static std::map<std::string, std::unique_ptr<IHash>> hashAlgorithms_map;
	};
}