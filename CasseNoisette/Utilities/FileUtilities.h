/*

FileUtilities: Un petite classe avec une couple de méthodes statiques
bien pratique pour faciliter les interactions avec les fichiers,
dans le but ultime de réduire la répétition de code.

@author Raphaël Doré

*/

namespace Utilities {
#pragma once
	class FileUtilities
	{
	public:
		static bool DoesFileExist(const std::string & _path);
		static bool IsFileEmpty(const std::string & _path);

		static std::string IncrementFileNameIfExists(const std::string & _path);

		static std::string GetFileContent(const std::string & _path);
		static std::string GetFileNameFromPath(const std::string & _path);
		static std::string GetBaseFileNameFromPath(const std::string & _path);
		static std::string GetFileExtension(const std::string & _fileName);
	};
}