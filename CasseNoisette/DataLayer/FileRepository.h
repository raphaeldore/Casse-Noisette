#pragma once

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
	class FileRepository
	{
	public:
		void loadPasswordFile(const string _pwdFilePath, string _separator = ":");
		const multimap<string, string> & getAllHashedPasswords() const;
	private:
		multimap<string, string> hashedPasswords;
		bool fileIsEmpty(ifstream& _file) const;
		vector<string> split(const string& _string, const string& _separator) const;
	};
}