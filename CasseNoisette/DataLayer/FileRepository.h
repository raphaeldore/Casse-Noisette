#pragma once
#include "stdafx.h"


using namespace std;

namespace DataLayer
{
	class FileRepository
	{
	public:
		void loadPasswordFile(const string _pwdFilePath);
		vector<string> getAllHashedPasswords();
	private:
		vector<string> hashedPasswords;
		bool fileIsEmpty(ifstream & _file) const;
	};

}