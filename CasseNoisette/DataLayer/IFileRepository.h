#pragma once

#include <queue>

namespace DataLayer
{
	class IFileRepository
	{
	public:
		virtual ~IFileRepository() {};

		virtual std::multimap<std::string, std::string> loadPasswordFile(const std::string & _pwdFilePath, const std::string & _separator) = 0;
		virtual std::unique_ptr<std::queue<std::string>> loadDictionaryFile(const std::string & _dictFilePath) = 0;
	};
}