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

	try{
		// On initialise crackEngine au bon type de CrackEngine
		switch (_crackEngineType)
		{
		case BRUTE_FORCE: {
			crackEngine = createBruteForce(move(crackEngine), _params);
			break;
		};
		case DICTIONARY: return nullptr; // TODO
		}

		// On ajoute ensuite les paramètres nécessaires à tous les types de CrackEngine
		DataLayer::FileRepository fileRepo;
		fileRepo.loadPasswordFile(_params[PWD_FILE_PATH]);

		crackEngine->setHashedPasswords(fileRepo.getAllHashedPasswords());
		crackEngine->setResultsFilePath(_params[RESULTS_FILE_PATH]);
		crackEngine->setPwdHashFunction(_params[HASH_TYPE]);
	}
	catch (const runtime_error & runtime_error)
	{
		cerr << string(__FUNCTION__) << ": " << runtime_error.what();
		return nullptr; // TODO: TEMP
	}
	catch (const exception & ex)
	{
		cerr << string(__FUNCTION__) << ": " << ex.what();
		return nullptr; // TODO: TEMP
	}
	
	return crackEngine;
}

unique_ptr<ICrackEngine> CrackFactory::createBruteForce(unique_ptr<ICrackEngine> _crackEngine, const CrackFactoryParams & _params) const
{
	string charset = _params.getParameterValue(CHARSET);
	int maxPwdLenght = stoi(_params.getParameterValue(MAX_PWD_LENGTH));

	_crackEngine = make_unique<BruteForce>(maxPwdLenght, charset);

	return move(_crackEngine);
}
