#pragma once

namespace Utilities {
	class DictionaryGenerator
	{
	public:
		DictionaryGenerator(const unsigned int _maxWordLength, const std::string & _charset, const std::string & _outputFilePath);
		~DictionaryGenerator();

		void GenerateDictionary();

	private:
		// Fonction récursive
		void generateWords(const unsigned int _wordLength, std::string _s);
		void flushBufferToFile();

		unsigned int maxWordLength;
		std::string charset;
		std::string outputFilePath;
		std::vector<std::string> buffer;
	};
}
