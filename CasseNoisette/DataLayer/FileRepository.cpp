#include "stdafx.h"
#include <fstream>

using namespace DataLayer;

void FileRepository::loadPasswordFile(const string _pwdFilePath)
{
	string line;
	ifstream ifile(_pwdFilePath.c_str());
	if (!ifile.is_open())
		throw runtime_error("File doesn't exits");

	while (getline(ifile, line))
	{
		hashedPasswords.push_back(line);
	}

	ifile.close();
}

vector<string> FileRepository::getAllHashedPasswords()
{
	return hashedPasswords;
}