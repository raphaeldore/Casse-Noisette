#include "stdafx.h"
#include "FileUtilities.h"

using namespace std;

FileUtilities::FileUtilities()
{
}


FileUtilities::~FileUtilities()
{
}

bool FileUtilities::DoesFileExist(const string & _path) {
	return tr2::sys::exists(_path);
}

bool FileUtilities::CreateFile(const string & _path, const bool & _overwriteExisting) {
	if (!_overwriteExisting) {
		return tr2::sys::create_directories(_path);
	}

	ofstream newFile(_path, std::fstream::trunc);

	if (newFile.good()) {
		newFile.close();
		return true;
	}

	newFile.close();
	return false;
}
