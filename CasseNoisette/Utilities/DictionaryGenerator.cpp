#include "stdafx.h"
#include "DictionaryGenerator.h"

using namespace std;
using namespace Utilities;

DictionaryGenerator::DictionaryGenerator(const unsigned int _maxWordLength,
                                         const string & _charset,
										 const string & _outputFilePath) : maxWordLength(_maxWordLength), charset(_charset), outputFilePath(_outputFilePath)
{
}


DictionaryGenerator::~DictionaryGenerator()
{
}

bool DictionaryGenerator::GenerateDictionary() {

}

void DictionaryGenerator::generateWords(const unsigned int _wordLength, string _s) {
	
	// Condition d'arrêt
	if (_wordLength == 0) {
		
		return;
	}

	for (register unsigned int i = 0; i < charset.size(); i++)
	{
		string appended = _s + charset[i];
		generateWords(_wordLength - 1, appended);
	}
}