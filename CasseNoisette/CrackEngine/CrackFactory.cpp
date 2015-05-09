#include "stdafx.h"
#include "CrackFactory.h"

using namespace CrackEngine;

map<string, unique_ptr<ICrackEngine>> CrackFactory::crackEngines_map;

CrackFactory::CrackFactory()
{
}

CrackFactory* CrackFactory::GetCrackFactory()
{
	static unique_ptr<CrackFactory> factoryInstance = make_unique<CrackFactory>();
	return factoryInstance.get();
}

unique_ptr<ICrackEngine> CrackFactory::CreateCrackEngine(const CRACK_ENGINE_TYPES & _crackEngineType, const CrackFactoryParams & _params) const
{
	unique_ptr<ICrackEngine> crackEngine;

	switch (_crackEngineType)
	{
	case BRUTE_FORCE:
		{
			crackEngine = createBruteForce(move(crackEngine), _params);
			break;
		}
	case DICTIONARY:
		{
			crackEngine = createDictionary(move(crackEngine), _params);
			break;
		}
	}

	// On ajoute ensuite les paramètres nécessaires à tous les types de CrackEngine
	DataLayer::FileRepository fileRepo;
	fileRepo.loadPasswordFile(_params[PWD_FILE_PATH], _params[SEPERATOR]);

	crackEngine->setHashedPasswords(fileRepo.getAllHashedPasswords());
	crackEngine->setResultsFilePath(_params[RESULTS_FILE_PATH]);
	crackEngine->setPwdHashFunction(_params[HASH_TYPE]);
	
	return crackEngine;
}

unique_ptr<ICrackEngine> CrackFactory::createBruteForce(unique_ptr<ICrackEngine> _crackEngine, const CrackFactoryParams & _params) const
{
	string charset = _params.getParameterValue(CHARSET);
	int maxPwdLenght = stoi(_params.getParameterValue(MAX_PWD_LENGTH));

	_crackEngine = make_unique<BruteForce>(maxPwdLenght, charset);

	return move(_crackEngine);
}

unique_ptr<ICrackEngine> CrackFactory::createDictionary(unique_ptr<ICrackEngine> _crackEngine, const CrackFactoryParams& _params) const
{
	DataLayer::FileRepository fileRepo;

	string dictionaryPath = _params[DICTIONARY_PATH];
	auto crackingDictionary = fileRepo.loadDictionaryFile(dictionaryPath);

	_crackEngine = make_unique<Dictionary>(move(crackingDictionary));

	return move(_crackEngine);
}