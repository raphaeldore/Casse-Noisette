#include "CrackingWorker.h"

CrackingWorker::CrackingWorker() : isRunning(false), isStopped(false)
{
}

const vector<tuple<string, string, string>> & CrackingWorker::getResults() const
{
	return results;
}

void CrackingWorker::startCracking()
{
	isStopped = false;
	isRunning = true;
	emit running();
	crack();
}

void CrackingWorker::stopCracking()
{
	isStopped = true;
	isRunning = false;
	crackEngine->cancelCrack();
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
		crackEngine = CrackFactory::GetCrackFactory()->CreateCrackEngine(engineType, crackFactoryParams);
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
		crackEngine->Crack();

		results = crackEngine->getResults();
		crackEngine.reset();

		emit resultsReady();
	}


	emit stopped();
}