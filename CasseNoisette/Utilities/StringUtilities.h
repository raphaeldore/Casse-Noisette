#pragma once

namespace Utilities {
	class StringUtilities
	{
	public:
		/*	Tr�s basique. Fonctionne seulement avec les caract�res d'un octet.
			Donc pas de UTF-8, seulement des caract�res ASCII.
		*/
		static std::string basicToLower(const std::string & _string);
	};
}