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
		void SetFileRepository(DataLayer::IFileRepository & _fileRepository);
	private:
		unique_ptr<ICrackEngine> createBruteForce(unique_ptr<ICrackEngine> _crackEngine, const CrackFactoryParams & _params) const;
		unique_ptr<ICrackEngine> createDictionary(unique_ptr<ICrackEngine> _crackEngine, const CrackFactoryParams & _params) const;

		DataLayer::IFileRepository * fileRepository;
		static map<string, unique_ptr<ICrackEngine>> crackEngines_map;
	};
}