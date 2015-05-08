#pragma once
#include "QObject.h"

#include "../CrackEngine/CrackFactoryParams.h"

using namespace CrackEngine;

class CrackingWorker :
	public QObject
{
	Q_OBJECT
public:
	CrackingWorker();
	void setCrackEngineType(const CRACK_ENGINE_TYPES & _crackEngineType);
	void setCrackFactoryParameters(const CrackFactoryParams & _crackFactoryParams);
	
	const vector<tuple<string, string, string>> & getResults() const;
signals:
	void resultsReady();
	void running();
	void stopped();
	void error(QString err);

public slots:
	void startCracking();
	void stopCracking();

private slots:
	void crack();
private:
	/*
	Volatile pour empêcher les optimisations par le compilateur.
	Car la valeur de isRunning et isStopped dépend de l'action de l'utilisateur.
	(et donc le compilateur ne peut déterminer leur valeur lors
	de la compilation).
	*/
	volatile bool isRunning, isStopped;
	CRACK_ENGINE_TYPES engineType;
	CrackFactoryParams crackFactoryParams;
	vector<tuple<string, string, string>> results;
};

