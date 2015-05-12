#pragma once
#include "stdafx.h"

using namespace std;

namespace DataLayer
{
	class IFileRepository
	{
	public:
		virtual ~IFileRepository() {};

		virtual multimap<string, string> loadPasswordFile(const string & _pwdFilePath, const string & _separator) = 0;
		virtual unique_ptr<queue<string>> loadDictionaryFile(const string & _dictFilePath) = 0;
		//virtual multimap<string, string> & getAllHashedPasswords() = 0;
	};
}