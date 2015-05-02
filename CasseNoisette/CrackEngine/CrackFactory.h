#pragma once
//#include "stdafx.h"

using namespace std;

namespace CrackEngine
{
	class ICrackEngine;

	enum CRACK_ENGINE_TYPES
	{
		BRUTE_FORCE,
		DICTIONARY
	};

	class CrackFactory
	{
	public:
		CrackFactory();
		static CrackFactory * GetCrackFactory();
		unique_ptr<ICrackEngine> CreateCrackEngine(const CRACK_ENGINE_TYPES & _crackEngineType, const CrackFactoryParams & _params) const;
	private:
		unique_ptr<BruteForce> createBruteForce(unique_ptr<ICrackEngine> _crackEngine, const CrackFactoryParams & _params) const;

		static map<string, unique_ptr<ICrackEngine>> crackEngines_map;
	};
}