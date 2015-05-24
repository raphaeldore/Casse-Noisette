#pragma once
#include "../DataLayer/IFileRepository.h"

class FakeFileRepository : public DataLayer::IFileRepository
{
public:
	FakeFileRepository();
	~FakeFileRepository();

	std::multimap<std::string, std::string> loadPasswordFile(const std::string & _pwdFilePath, const std::string & _separator);
	std::unique_ptr<std::queue<std::string>> loadDictionaryFile(const std::string & _dictFilePath);

	bool hasLoadPasswordFileBeenCalled();
	bool hasLoadDictionaryFileBeenCalled();

private:
	bool loadPasswordFileHasBeenCalled;
	bool loadDictionaryFileHasBeenCalled;
};