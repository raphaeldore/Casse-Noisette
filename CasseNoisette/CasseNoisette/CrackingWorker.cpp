#include "CrackingWorker.h"
#include "../DataLayer/FileRepository.h"

CrackingWorker::CrackingWorker() : isRunning(false), isStopped(false)
{
	crackFactory = CrackFactory::GetCrackFactory();
	crackFactory->SetFileRepository(make_unique<DataLayer::FileRepository>());
}

const vector<tuple<string, string, string>> & CrackingWorker::getResults() const
{
	return results;
}

void CrackingWorker::startCracking()
{
	isStopped = false;
	isRunning = true;
	crack();
	emit resultsReady();
	emit unloadingEngine();
	crackEngine.reset();
	emit stopped();
}

void CrackingWorker::stopCracking()
{
	isStopped = true;
	isRunning = false;
	if (crackEngine != nullptr)	crackEngine->cancelCrack();
	emit stopped();
}

void CrackingWorker::setCrackEngineType(const CRACK_ENGINE_TYPES& _crackEngineType)
{
	engineType = _crackEngineType;
}

void CrackingWorker::setCrackFactoryParameters(const CrackFactoryParams& _crackFactoryParams)
{
	crackFactoryParams = _crackFactoryParams;
}

void CrackingWorker::crack()
{
	if (!isRunning || isStopped) return;

	try
	{
		emit creatingEngine();
		crackEngine = crackFactory->CreateCrackEngine(engineType, crackFactoryParams);
		emit engineCreated();
	}
	catch (const exception & ex)
	{
		QString factoryError(ex.what());
		emit error(factoryError);
		emit stopped();
		return;
	}


	if (crackEngine != nullptr)
	{
		emit running();
		crackEngine->Crack();

		results = crackEngine->getResults();
	}
}