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

	while (getline(ifile, line))
	{
		string default_user = "no_user";

		auto pos = line.find(_separator);

		if (pos == string::npos)
		{
			hashedPasswords.push_back(make_tuple(default_user, line, ""));
		}
		else
		{
			vector<string> lineSplit = split(line, _separator);

			if (lineSplit.size() == 2)
			{
				hashedPasswords.push_back(make_tuple(lineSplit[0], lineSplit[1], ""));
			}
			else
			{
				throw invalid_argument("File format is not valid.");
			}
		}
	}

	ifile.close();
}

vector<tuple<string, string, string>> FileRepository::getAllHashedPasswords() const
{
	return hashedPasswords;
}

bool FileRepository::fileIsEmpty(ifstream& _file) const
{
	return _file.peek() == std::ifstream::traits_type::eof();
}

vector<string> FileRepository::split(const string& _string, const string& _separator) const
{
	/* https://ysonggit.github.io/coding/2014/12/16/split-a-string-using-c.html */
	vector<string> returnVector;

	auto i = 0;
	auto pos = _string.find(_separator);
	while (pos != string::npos)
	{
		returnVector.push_back(_string.substr(i, pos - i));
		pos += _separator.length();
		i = pos;
		pos = _string.find(_separator, pos);

		if (pos == string::npos)
			returnVector.push_back(_string.substr(i, _string.length()));
	}

	return returnVector;
}