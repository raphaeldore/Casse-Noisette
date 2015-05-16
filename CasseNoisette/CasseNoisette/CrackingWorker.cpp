#include "CrackingWorker.h"
#include "../DataLayer/FileRepository.h"

CrackingWorker::CrackingWorker() : isRunning(false), isStopped(false)
{
	crackFactory = CrackFactory::GetCrackFactory();
	fileRepository = make_unique<DataLayer::FileRepository>();
	crackFactory->SetFileRepository(*fileRepository);
}

vector<tuple<string, string, string>> CrackingWorker::getResults() const
{
	return results;
}

void CrackingWorker::startCracking()
{
	isStopped = false;
	isRunning = true;

	crack();

	// S'il n'y a eu aucune erreur durant le cassage,
	// ou si l'utilisateur ne quitte pas l'application,
	// alors on informe à ceux qui écoutent que les
	// résultats sont prêts.
	if (!wasError && !exitWasCalled)
	{
		emit resultsReady();
	}

	emit unloadingEngine();
	crackEngine.reset();
	emit stopped();

	isStopped = true;
	isRunning = false;
}

void CrackingWorker::stopCracking()
{
	if (isRunning)
	{
		crackEngine->cancelCrack();
		isStopped = true;
		isRunning = false;
	}
}

void CrackingWorker::exit()
{
	exitWasCalled = true;
	stopCracking();
	emit exited();
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
		wasError = true;
		return;
	}
	
	if (crackEngine != nullptr)
	{
		// On informe à ceux qui écoutent qu'on commence le cassage
		emit running();

		crackEngine->Crack();

		wasError = false;

		results = crackEngine->getResults();
	}
}