#include "stdafx.h"
#include <fstream>

using namespace DataLayer;

void FileRepository::loadPasswordFile(const string _pwdFilePath)
{
	ifstream ifile(_pwdFilePath.c_str());
	if (!ifile)
		throw runtime_error("File doesn't exits");
}

vector<string> FileRepository::getAllHashedPasswords()
{
	return hashedPasswords;
}