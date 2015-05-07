#include "CrackingWorker.h"
//#include "../CrackEngine/CrackFactory.h"

CrackingWorker::CrackingWorker(const CRACK_ENGINE_TYPES & _crackEngineType, const CrackFactoryParams& _crackFactoryParams)
{
	//resultsReference = _resultsReference;
	engineType = CrackEngine::BRUTE_FORCE;
	crackFactoryParams = _crackFactoryParams;
}

vector<string> CrackingWorker::getResults()
{
	return results;
}

void CrackingWorker::startCracking()
{
	unique_ptr<ICrackEngine> crackEngine = CrackFactory::GetCrackFactory()->CreateCrackEngine(engineType, crackFactoryParams);
	QVector<string> results_qt = QVector<string>::fromStdVector(results);
	crackEngine->Crack();
	
	//results = crackEngine->getResults();

	//*resultsReference = QVector<string>::fromStdVector(results);

	//emit resultsReady(results_qt);

	results = crackEngine->getResults();

	emit resultsReady(results);
}