#pragma once
#include "stdafx.h"

using namespace std;

namespace DataLayer{
	class IFileRepository{
	public:
		void loadPasswordFile(const string & _pwdFilePath, const string & _separator = ":");
		unique_ptr<queue<string>> loadDictionaryFile(const string & _dictFilePath);
		const multimap<string, string> & getAllHashedPasswords() const;
	private:
	};
}