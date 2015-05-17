#pragma once
#include "QObject.h"

#include "../CrackEngine/CrackFactoryParams.h"
#include <memory>


namespace CrackEngine
{
	enum CRACK_ENGINE_TYPES;
	class CrackFactoryParams;
	class ICrackEngine;
	class CrackFactory;
}

namespace DataLayer
{
	class IFileRepository;
}

using namespace CrackEngine;

class CrackingWorker :
	public QObject
{
	Q_OBJECT
public:
	CrackingWorker();
	void setCrackEngineType(const CRACK_ENGINE_TYPES & _crackEngineType);
	void setCrackFactoryParameters(const CrackEngine::CrackFactoryParams & _crackFactoryParams);
	
	std::vector<std::tuple<std::string, std::string, std::string>> getResults() const;
signals:
	void creatingEngine();
	void engineCreated();
	void unloadingEngine();
	void resultsReady();
	void running();
	void stopped();
	void exited();
	void error(QString err);

public slots:
	void startCracking();
	void stopCracking();
	void exit();

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
	bool wasError = false;
	bool exitWasCalled = false;
	CRACK_ENGINE_TYPES engineType;
	CrackEngine::CrackFactoryParams crackFactoryParams;
	std::unique_ptr<CrackEngine::ICrackEngine> crackEngine;
	CrackEngine::CrackFactory * crackFactory;
	std::unique_ptr<DataLayer::IFileRepository> fileRepository;
	std::vector<std::tuple<std::string, std::string, std::string>> results;
};

