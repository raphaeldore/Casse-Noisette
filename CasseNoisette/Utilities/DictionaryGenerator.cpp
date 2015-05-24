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

	// On vide le fichier s'il existe déjà
	if (FileUtilities::DoesFileExist(_outputFilePath)) FileUtilities::ClearFileContent(_outputFilePath);
}


DictionaryGenerator::~DictionaryGenerator()
{
}

void DictionaryGenerator::GenerateDictionary() {
	for (unsigned int i = 1; i <= maxWordLength; ++i) {
		string initialString = "";
		generateWords(i, initialString);
		flushBufferToFile();
		buffer.clear();
	}
}

void DictionaryGenerator::generateWords(const unsigned int _wordLength, string _s) {

	// Condition d'arrêt
	if (_wordLength == 0) {
		if (buffer.size() == 1000000) {
			// On prends le contenu du vector et on l'envoi dans le fichier
			flushBufferToFile();
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

void DictionaryGenerator::flushBufferToFile()
{
	// On veut être le seul à écrire dans le fichier
	static mutex mutex;

	// On vérouille le mutex avant d'accèder au fichier
	lock_guard<std::mutex> lock(mutex);

	// On tente d'écrire dans le fichier
	ofstream outputFile(outputFilePath, ofstream::out | ofstream::app);
	if (!outputFile.is_open())
		throw runtime_error("Je suis incapable d'ouvrir le fichier :(");

	// On ajoute toutes les combinaisons de mots du vecteur dans le fichier
	for (const auto & combination : buffer)
	{
		outputFile << combination + "\n";
	}

	// On vide enfin le vecteur
	buffer.clear();

	// outputFile est fermé automatiquement.
}