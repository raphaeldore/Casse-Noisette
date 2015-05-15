#pragma once
#include "../DataLayer/IFileRepository.h"

class FakeFileRepository : public DataLayer::IFileRepository
{
public:
	FakeFileRepository();
	~FakeFileRepository();

	multimap<string, string> loadPasswordFile(const string & _pwdFilePath, const string & _separator);
	unique_ptr<queue<string>> loadDictionaryFile(const string & _dictFilePath);

	bool hasLoadPasswordFileBeenCalled();
	bool hasLoadDictionaryFileBeenCalled();

private:
	bool loadPasswordFileHasBeenCalled;
	bool loadDictionaryFileHasBeenCalled;
};