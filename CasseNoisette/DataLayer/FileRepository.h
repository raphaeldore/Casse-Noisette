#pragma once

#include "IFileRepository.h"

namespace DataLayer
{
	class FileRepository : public IFileRepository
	{
	public:
		FileRepository();
		~FileRepository() override;

		std::multimap<std::string, std::string> loadPasswordFile(const std::string & _pwdFilePath, const std::string & _separator = ":") override;
		std::unique_ptr<std::queue<std::string>> loadDictionaryFile(const std::string & _dictFilePath) override;

	private:
		static bool split(const std::string& _string, const std::string& _separator, std::vector<std::string> & _outVector);
	};
}