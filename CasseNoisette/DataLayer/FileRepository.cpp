#include "stdafx.h"
#include "FileRepository.h"

using namespace DataLayer;

FileRepository::FileRepository()
{
}

FileRepository::~FileRepository()
{
}

multimap<string, string> FileRepository::loadPasswordFile(const string & _pwdFilePath, const string & _separator)
{
	string line;
	ifstream ifile(_pwdFilePath.c_str());
	if (!ifile.is_open())
		throw runtime_error("File doesn't exits");

	if (fileIsEmpty(ifile))
	{
		ifile.close();
		throw logic_error("The file is empty");
	}

	multimap<string, string> hashedPasswords;

	while (getline(ifile, line))
	{
		string default_user = "no_user";

		auto pos = line.find(_separator);

		if (pos == string::npos)
		{
			// Ligne sans séparateur. Donc un password haché non lié à un nom d'utilisateur
			hashedPasswords.insert(make_pair(line, default_user));
		}
		else
		{
			vector<string> lineSplit;

			if (split(line, _separator, lineSplit) && lineSplit.size() == 2)
			{
				hashedPasswords.insert(make_pair(lineSplit[1], lineSplit[0]));
			}
			else
			{
				throw invalid_argument("File format is not valid.");
			}
		}
	}

	ifile.close();

	return hashedPasswords;
}

unique_ptr<queue<string>> FileRepository::loadDictionaryFile(const string& _dictFilePath)
{
	MemoryMapped dictionaryFile(_dictFilePath, MemoryMapped::WholeFile, MemoryMapped::SequentialScan);

	if (!dictionaryFile.isValid()) throw runtime_error("Le fichier dictionnaire n'existe pas.");

	// Sur le Heap car le Stack est trop petit (pour les gros fichiers)
	unique_ptr<queue<string>> dictionary = make_unique<queue<string>>();

	const unsigned char * buffer = dictionaryFile.getData();

	for (uint64_t i = 0; i < dictionaryFile.size(); i++)
	{
		// On ignore les fins de lignes et les retours de chariot (1 mot par ligne)
		if (buffer[i] == '\n' || buffer[i] == '\r') continue;

		string line;

		do
		{
			line += buffer[i];
			i++;
		} while (i < dictionaryFile.size() && buffer[i] != '\n' && buffer[i] != '\r');

		dictionary->push(line);

	}

	return move(dictionary);
}

bool FileRepository::fileIsEmpty(ifstream& _file)
{
	return _file.peek() == ifstream::traits_type::eof();
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