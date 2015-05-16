#include "stdafx.h"
#include "FileUtilities.h"

using namespace std;
using namespace Utilities;

bool FileUtilities::DoesFileExist(const string & _path) {
	return tr2::sys::exists(tr2::sys::path(_path));
}

bool FileUtilities::IsFileEmpty(const string & _path) {
	return tr2::sys::is_empty(tr2::sys::path(_path));
}

string FileUtilities::IncrementFileNameIfExists(const string & _path)
{
	// Pas la manière la plus élégante... Mais ça marche!

	if (!DoesFileExist(_path)) return _path;

	string originalFileName = GetBaseFileNameFromPath(_path);
	string pathAttempt;
	unsigned int increment = 1;
	do
	{
		pathAttempt = _path; // On reset le path
		string newFileName = originalFileName + to_string(increment);
		pathAttempt.replace(pathAttempt.find(originalFileName), newFileName.size() - 1, newFileName);
		++increment;
	} while (DoesFileExist(pathAttempt));

	return pathAttempt;
}

void FileUtilities::ClearFileContent(const std::string& _path)
{
	if (!DoesFileExist(_path)) throw runtime_error("Le fichier n'existe pas!");

	ofstream file;

	file.open(_path, ofstream::out | ofstream::trunc);

	if (!file.is_open()) throw runtime_error("Je suis incapable d'ouvrir le fichier :(");

	file.close();
}

string FileUtilities::GetFileContent(const string& _path)
{
	if (!DoesFileExist(_path)) throw runtime_error("Le fichier n'existe pas!");

	ifstream file(_path, ifstream::in);

	if (!file.is_open()) throw runtime_error("Je suis incapable d'ouvrir le fichier :(");

	string fileContent((istreambuf_iterator<char>(file)),
		istreambuf_iterator<char>());

	return fileContent;
}

string FileUtilities::GetFileNameFromPath(const string& _path)
{
	string seperator = "/"; // Séparateur Unix

	// Dans l'intérêt de coder une classe portable...
#ifdef _WIN32
	seperator = '\\'; // Séparateur Windows
#endif

	auto startFrom = _path.find_last_of(seperator) + 1;
	string fileName = _path.substr(startFrom, _path.length() - 1);

	return fileName;
}

string FileUtilities::GetBaseFileNameFromPath(const string& _path)
{
	string fileNameWithExtension = GetFileNameFromPath(_path);
	auto stopPosition = fileNameWithExtension.find_last_of('.');
	string baseFileName = fileNameWithExtension.substr(0, stopPosition);

	return baseFileName;
}

string FileUtilities::GetFileExtension(const string& _fileName)
{
	auto startFrom = _fileName.find_last_of('.') + 1;
	string fileNameExtension = _fileName.substr(startFrom, _fileName.length() - 1);

	return fileNameExtension;
}