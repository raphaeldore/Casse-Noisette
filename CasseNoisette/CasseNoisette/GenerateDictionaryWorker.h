#pragma once
#include "QObject.h"
#include <memory>


namespace Utilities
{
	class DictionaryGenerator;
}

class GenerateDictionaryWorker :
	public QObject
{
	Q_OBJECT
public:
	GenerateDictionaryWorker();
	~GenerateDictionaryWorker();
public slots:
	void setGenerationParameters(const int & _maxLenght, const std::string & _charset, const std::string & _outputFile);
private slots:
	void startGeneration();
signals:
	void generationStarted();
	void generationFinished();
	void error(QString err);
private:
	std::unique_ptr<Utilities::DictionaryGenerator> dictionaryGenerator;
	int maxLength = 0;
	std::string charset = "";
	std::string outputFile = "";
};

