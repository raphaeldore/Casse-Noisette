#include "GenerateDictionaryWorker.h"


GenerateDictionaryWorker::GenerateDictionaryWorker()
{
	
}


GenerateDictionaryWorker::~GenerateDictionaryWorker()
{
}

void GenerateDictionaryWorker::setGenerationParameters(const int& _maxLenght, const std::string& _charset, const std::string& _outputFile)
{
	maxLength = _maxLenght;
	charset = _charset;
	outputFile = _outputFile;
}

void GenerateDictionaryWorker::startGeneration()
{
	try
	{
		dictionaryGenerator = std::make_unique<Utilities::DictionaryGenerator>(maxLength, charset, outputFile);
		emit generationStarted();
		dictionaryGenerator->GenerateDictionary();
		emit generationFinished();
		dictionaryGenerator.reset();
		return;
	}
	catch (const std::exception & ex)
	{
		QString exception_error(ex.what());
		emit error(exception_error);
		return;
	}

	
}