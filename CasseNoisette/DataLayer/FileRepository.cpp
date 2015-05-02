#include "stdafx.h"
#include <fstream>

using namespace DataLayer;

void FileRepository::loadPasswordFile(const string _pwdFilePath)
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

bool FileRepository::fileIsEmpty(ifstream& _file) const
{
	return _file.peek() == std::ifstream::traits_type::eof();
}