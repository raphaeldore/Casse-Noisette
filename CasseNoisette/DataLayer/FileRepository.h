#pragma once
#include <queue>

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
	class FileRepository : public FileRepository
	{
	public:
		void loadPasswordFile(const string & _pwdFilePath, const string & _separator = ":");
		unique_ptr<queue<string>> loadDictionaryFile(const string & _dictFilePath);
		const multimap<string, string> & getAllHashedPasswords() const;

	private:
		multimap<string, string> hashedPasswords;
		bool fileIsEmpty(ifstream& _file) const;
		static vector<string> split(const string& _string, const string& _separator);
	};
}