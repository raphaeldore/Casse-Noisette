#pragma once

namespace Utilities {
	class StringUtilities
	{
	public:
		/*	Très basique. Fonctionne seulement avec les caractères d'un octet.
			Donc pas de UTF-8, seulement des caractères ASCII.
		*/
		static std::string basicToLower(const std::string & _string);
	};
}