/*

FileUtilities: Un petite classe avec une couple de m�thodes statiques
qui offre quelques fonctions bien pratique pour int�ragir
avec des fichiers.

@author Rapha�l Dor�

*/

namespace Utilities {
#pragma once
	class FileUtilities
	{
	public:
		FileUtilities();
		~FileUtilities();

		static bool DoesFileExist(const std::string & _path);
		static bool IsFileEmpty(const std::string & _path);
		static bool CreateFile(const std::string & _path, const bool & _overwriteExisting = false);
		static void AppendVectorContentToFile(const std::string & _path, const std::vector<std::string> & _vector);
		static void AppendStringToFile(std::ofstream & _file, const std::string & _string);
	};
}