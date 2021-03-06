#include "stdafx.h"
#include "FileRepository.h"
#include "../Utilities/StringUtilities.h"

using namespace DataLayer;
using namespace Utilities;
using namespace std;

FileRepository::FileRepository()
{
}

FileRepository::~FileRepository()
{
}

multimap<string, string> FileRepository::loadPasswordFile(const string & _pwdFilePath, const string & _separator)
{
	if (!FileUtilities::DoesFileExist(_pwdFilePath)) throw runtime_error("Le fichier de mots de passe n'existe pas.");
	if (FileUtilities::IsFileEmpty(_pwdFilePath)) throw runtime_error("Le fichier de mots de passe est vide.");

	string line;
	ifstream ifile(_pwdFilePath.c_str());
	if (!ifile.is_open()) throw runtime_error("Impossible de lire le fichier: " + string(_pwdFilePath));

	multimap<string, string> hashedPasswords;

	while (getline(ifile, line))
	{
		string default_user = "no_user";

		auto pos = line.find(_separator);

		pair<string, string> pwdLine;

		if (pos == string::npos)
		{
			
			// Ligne sans séparateur. Donc un password haché non lié à un nom d'utilisateur
			pwdLine = make_pair(StringUtilities::basicToLower(line), default_user);
		}
		else
		{
			vector<string> lineSplit;

			if (split(line, _separator, lineSplit) && lineSplit.size() == 2)
			{
				pwdLine = make_pair(StringUtilities::basicToLower(lineSplit[1]), lineSplit[0]);
			}
			else
			{
				throw invalid_argument("Le format du fichier est invalide");
			}
		}

		// Un hash doit être en Hexadécimal, donc les seuls caractères permis sont: 0 à 9, et les lettres de a à f.
		if (!hashContainsValidCharacters(pwdLine.first)) throw runtime_error("Le fichier fournis contient des hashs invalides, ou n'est pas un fichier valide.");

		hashedPasswords.insert(pwdLine);
	}

	ifile.close();

	return hashedPasswords;
}

unique_ptr<queue<string>> FileRepository::loadDictionaryFile(const string& _dictFilePath)
{
	if (!FileUtilities::DoesFileExist(_dictFilePath)) throw runtime_error("Le fichier dictionnaire n'existe pas.");
	if (FileUtilities::IsFileEmpty(_dictFilePath))  throw runtime_error("Le fichier dictionnaire est vide.");

	MemoryMapped dictionaryFile(_dictFilePath, MemoryMapped::WholeFile, MemoryMapped::SequentialScan);

	if (!dictionaryFile.isValid()) throw runtime_error("Impossible de lire le fichier dictionnaire fournis.");

	// Sur le Heap car le Stack est trop petit (pour les gros fichiers)
	unique_ptr<queue<string>> dictionary = make_unique<queue<string>>();

	const unsigned char * buffer = dictionaryFile.getData();

	for (uint64_t i = 0; i < dictionaryFile.size(); i++)
	{
		// On ignore les fins de lignes et les retours de chariot (1 mot par ligne)
		if (buffer[i] == '\n' || buffer[i] == '\r') continue;

		string line;

		// On va ensuite chercher tous les charactères de la ligne
		// et on arrête lorsqu'on arrive à la fin de la ligne.
		do
		{
			line += buffer[i];
			i++;
		} while (i < dictionaryFile.size() && buffer[i] != '\n' && buffer[i] != '\r');

		dictionary->push(line);

	}

	return move(dictionary);
}

bool FileRepository::split(const string& _string, const string& _separator, vector<string>& _outVector)
{
	/* https://ysonggit.github.io/coding/2014/12/16/split-a-string-using-c.html */

	_outVector.clear();

	auto i = 0;
	auto pos = _string.find(_separator);
	while (pos != string::npos)
	{
		// On prend la partie avant le séparateur
		_outVector.push_back(_string.substr(i, pos - i));
		pos += _separator.length();
		i = pos;
		pos = _string.find(_separator, pos);

		// On prend la partie après le séparateur
		if (pos == string::npos)
			_outVector.push_back(_string.substr(i, _string.length()));
	}

	if (_outVector.empty()) return false;

	return true;
}

bool FileRepository::hashContainsValidCharacters(const std::string& _hash)
{
	return regex_match(_hash, regex("^[a-f0-9]*$"));
}