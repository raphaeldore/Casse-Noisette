#pragma once

#include <queue>

#include "IFileRepository.h"

/*

TODO:
- Validation du contenu du fichier
- Utilisation d'un séparateur (ex: username:hashedPassword)
- Validation du formatage de chaque lignes du fichier
- Bref, de la robustesse.
*/

using namespace std;

namespace DataLayer
{
	class FileRepository : public IFileRepository
	{
	public:
		FileRepository();
		~FileRepository() override;

		multimap<string, string> loadPasswordFile(const string & _pwdFilePath, const string & _separator = ":") override;
		unique_ptr<queue<string>> loadDictionaryFile(const string & _dictFilePath) override;

	private:
		static bool fileIsEmpty(ifstream& _file);
		static vector<string> split(const string& _string, const string& _separator);
	};
}