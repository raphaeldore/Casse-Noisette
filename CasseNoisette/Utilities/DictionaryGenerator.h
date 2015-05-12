#pragma once

namespace Utilities {
	class DictionaryGenerator
	{
	public:
		DictionaryGenerator(const unsigned int _maxWordLength, const string & _charset, const string & _outputFilePath);
		~DictionaryGenerator();

		bool GenerateDictionary();

	private:
		// Fonction récursive
		void generateWords(const unsigned int _wordLength, string _s);

		unsigned int maxWordLength;
		string charset;
		string outputFilePath;
	};
}
