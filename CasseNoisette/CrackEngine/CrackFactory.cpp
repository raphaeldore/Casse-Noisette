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
	unique_ptr<ICrackEngine> crackEngine = make_unique<ICrackEngine>();

	try{
		// Paramètres obligatoires pour chaque type de CrackEngine
		//crackEngine->setPwdFilePath(_params.getParameterValue(PWD_FILE_PATH));
		//crackEngine->setResultsFilePath(_params.getParameterValue(RESULTS_FILE_PATH));
		//crackEngine->setPwdHashFunction(_params.getParameterValue(HASH_TYPE));

		crackEngine->setPwdFilePath(_params[PWD_FILE_PATH]);
		crackEngine->setResultsFilePath(_params[RESULTS_FILE_PATH]);
		crackEngine->setPwdHashFunction(_params[HASH_TYPE]);

		// On ajoute ensuite les paramètres nécessaires chaque type de CrackEngine
		switch (_crackEngineType)
		{
		case BRUTE_FORCE: {
			return createBruteForce(move(crackEngine), _params);
		};
		case DICTIONARY: break;
		default: break;
		}
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

	//return make_unique<BruteForce>("abcdef");
}

unique_ptr<BruteForce> CrackFactory::createBruteForce(unique_ptr<ICrackEngine> _crackEngine, const CrackFactoryParams & _params) const
{
	// Avec les unique_ptr, le polymorphisme c'est un peu plus compliqué :P
	// J'ai trouvé comment faire ici: http://stackoverflow.com/questions/17417848/stdunique-ptr-with-derived-class

	BruteForce *tmp = dynamic_cast<BruteForce*>(_crackEngine.get());
	unique_ptr<BruteForce> bruteForceInstance;
	if (tmp != nullptr)
	{
		_crackEngine.release();
		bruteForceInstance.reset(tmp);
	}

	bruteForceInstance->setCrackingCharset(_params.getParameterValue(CHARSET));
	bruteForceInstance->setMaxPwdLenght(stoi(_params.getParameterValue(MAX_PWD_LENGTH)));

	return move(bruteForceInstance);
}