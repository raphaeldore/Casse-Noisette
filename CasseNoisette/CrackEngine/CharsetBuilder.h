#pragma once

namespace CrackEngine
{
	/* Les différents groupes de caractères que nous supportons */
	namespace Charsets
	{
		static const std::string loweralpha = "abcdefghijklmnopqrstuvwxyz";
		static const std::string upperalpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		static const std::string numeric = "0123456789";
		static const std::string space = " ";
		static const std::string special = "!@#$%^&*()-_+=";
	}

	class CharsetBuilder
	{
	public:
		CharsetBuilder();
		CharsetBuilder(const bool _loweralpha, const bool _upperalpha, const bool _numeric, const bool _space, const bool _special, const std::string & _customCharset = "");

		// Si l'utilisateur préfère ne pas passer par le constructeur
		void enableLowerAlpha();
		void enableUpperAlpha();
		void enableNumeric();
		void enableSpace();
		void enableSpecial();
		void addCustomCharset(const std::string & _customCharset);

		std::string BuildCharset();

	private:
		std::string removeDuplicateCharacters(std::string _generatedCharset) const;

		bool loweralpha;
		bool upperalpha;
		bool numeric;
		bool space;
		bool special;

		std::string customCharset;
	};
}