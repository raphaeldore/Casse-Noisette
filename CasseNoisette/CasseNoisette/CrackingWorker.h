#pragma once
#include "QObject.h"
#include <QtCore/qvector.h>

//#include "../CrackEngine/ICrackEngine.h"
#include "../CrackEngine/CrackFactoryParams.h"
//#include "../CrackEngine/CrackFactory.h"

using namespace CrackEngine;

//#include "../CrackEngine/ICrackEngine.h"


class CrackingWorker :
	public QObject
{
	Q_OBJECT
public:
	CrackingWorker(const CRACK_ENGINE_TYPES & _crackEngineType, const CrackFactoryParams & _crackFactoryParams);
	vector<string> getResults();
public slots:
	//CrackingWorker(CrackEngine::ICrackEngine * _crackEngine);
	//CrackingWorker(const CrackFactoryParams & _crackFactoryParams);

	void startCracking();

signals:
	void resultsReady(const vector<string> _results);
private:
	CRACK_ENGINE_TYPES engineType;
	CrackFactoryParams crackFactoryParams;
	vector<string> results;
};

