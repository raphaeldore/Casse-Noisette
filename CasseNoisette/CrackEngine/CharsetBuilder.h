#pragma once

namespace CrackEngine
{
	class CharsetBuilder
	{
	public:
		CharsetBuilder();
		CharsetBuilder(const bool _loweralpha, const bool _upperalpha, const bool _numeric, const bool _space, const bool _special);

		// Si l'utilisateur préfère ne pas passer par le constructeur
		void enableLowerAlpha();
		void enableUpperAlpha();
		void enableNumeric();
		void enableSpace();
		void enableSpecial();

		string BuildCharset();

	private:
		bool loweralpha;
		bool upperalpha;
		bool numeric;
		bool space;
		bool special;
	};
}