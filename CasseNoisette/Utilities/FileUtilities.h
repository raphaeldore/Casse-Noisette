/*

FileUtilities: Un petite classe avec une couple de méthodes statiques
qui offre quelques fonctions bien pratique pour intéragir
avec des fichiers.

@author Raphaël Doré

*/

namespace Utilities {
#pragma once
	class FileUtilities
	{
	public:
		FileUtilities();
		~FileUtilities();

		static bool DoesFileExist(const string & _path);
		static bool CreateFile(const string & _path, const bool & _overwriteExisting = false);
	};
}