#include "stdafx.h"
#include "DictionaryGenerator.h"
#include "FileUtilities.h"

using namespace std;
using namespace Utilities;

DictionaryGenerator::DictionaryGenerator(const unsigned int _maxWordLength,
                                         const string & _charset,
										 const string & _outputFilePath) : maxWordLength(_maxWordLength), charset(_charset), outputFilePath(_outputFilePath)
{
	buffer.reserve(500000);
}


DictionaryGenerator::~DictionaryGenerator()
{
}

void DictionaryGenerator::GenerateDictionary() {
	for (unsigned int i = 0; i <= maxWordLength; ++i) {
		string initialString = "";
		generateWords(i, initialString);
		Utilities::FileUtilities::AppendVectorContentToFile(outputFilePath, buffer);
		buffer.clear();
	}
}

void DictionaryGenerator::generateWords(const unsigned int _wordLength, string _s) {
	
	// Condition d'arrêt
	if (_wordLength == 0) {
		if (buffer.size() == 500000) {
			// On prends le contenu du vector et on l'envoi dans le fichier
			Utilities::FileUtilities::AppendVectorContentToFile(outputFilePath, buffer);
			buffer.clear();
		}

		buffer.push_back(_s);

		return;
	}

	for (register unsigned int i = 0; i < charset.size(); i++)
	{
		string appended = _s + charset[i];
		generateWords(_wordLength - 1, appended);
	}
}