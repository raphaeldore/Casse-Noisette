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
	unique_ptr<ICrackEngine> crackEngine;

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

	crackEngine->Crack();

	results = crackEngine->getResults();

	emit resultsReady();
	emit stopped();
}