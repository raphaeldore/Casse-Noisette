#include "stdafx.h"
#include <fstream>

using namespace DataLayer;

void FileRepository::loadPasswordFile(const string _pwdFilePath, string _separator)
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

	tuple<string, string, string> hashedPwdTuple;

	while (getline(ifile, line))
	{
		string user = "no_user";
		string hashedPwd;

		vector<string> lineSplit = split(line, _separator);

		if (lineSplit.size() == 1)
		{
			hashedPwd = lineSplit[0];
		}
		else if (lineSplit.size() == 2)
		{
			user = lineSplit[0];
			hashedPwd = lineSplit[1];
		}
		else
		{
			throw invalid_argument("File format is not valid.");
		}

		hashedPwdTuple = make_tuple(user, hashedPwd, ""); //tuple<string, string, string>{user, hashedPwd, ""};

		hashedPasswords.push_back(hashedPwdTuple);
	}

	ifile.close();
}

vector<tuple<string,string,string>> FileRepository::getAllHashedPasswords() const
{
	return hashedPasswords;
}

bool FileRepository::fileIsEmpty(ifstream& _file) const
{
	return _file.peek() == std::ifstream::traits_type::eof();
}

vector<string> FileRepository::split(const string& _string, const string& _separator) const
{
	vector<string> returnVector;
	string::size_type i = 0;
	string::size_type j = _string.find(_separator);

	do {
		returnVector.push_back(_string.substr(i, j - i));
		i = ++j;
		j = _string.find(_separator, j);

		//if (j == string::npos)
			//returnVector.push_back(_string.substr(i, _string.length()));
	} while (j != string::npos);

	return returnVector;
}