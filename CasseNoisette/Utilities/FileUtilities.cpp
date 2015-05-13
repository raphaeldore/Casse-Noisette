#include "stdafx.h"
#include "FileUtilities.h"

using namespace std;
using namespace Utilities;

FileUtilities::FileUtilities()
{
}

FileUtilities::~FileUtilities()
{
}

bool FileUtilities::DoesFileExist(const string & _path) {
	return tr2::sys::exists(tr2::sys::path(_path));
}

bool FileUtilities::IsFileEmpty(const string & _path) {
	return tr2::sys::is_empty(tr2::sys::path(_path));
}

bool FileUtilities::CreateFile(const string & _path, const bool & _overwriteExisting) {
	if (DoesFileExist(_path) && !_overwriteExisting) return false;

	tr2::sys::path path(_path);

	fstream newFile;
	newFile.open(path, std::fstream::binary | std::fstream::out);

	if (newFile.good()) {
		newFile.close();
		return true;
	}

	newFile.close();
	return false;
}

void FileUtilities::AppendVectorContentToFile(const std::string & _path, const std::vector<string> & _vector) {
	if (!DoesFileExist(_path)) {
		if (!CreateFile(_path)) return;
	}

	ofstream file(_path, ofstream::out | ofstream::app);

	for (const auto & word : _vector) {
		AppendStringToFile(file, word);
	}

	file.close();
}

void FileUtilities::AppendStringToFile(std::ofstream & _file, const string & _string) {
	_file << _string << "\n";
}