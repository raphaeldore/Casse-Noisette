#pragma once

namespace DataLayer{
	class IFileRepository;
}

namespace CrackEngine
{
	class CrackFactoryParams;
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
		std::unique_ptr<ICrackEngine> CreateCrackEngine(const CRACK_ENGINE_TYPES & _crackEngineType, const CrackFactoryParams & _params) const;
		void SetFileRepository(DataLayer::IFileRepository & _fileRepository);
	private:
		std::unique_ptr<ICrackEngine> createBruteForce(std::unique_ptr<ICrackEngine> _crackEngine, const CrackFactoryParams & _params) const;
		std::unique_ptr<ICrackEngine> createDictionary(std::unique_ptr<ICrackEngine> _crackEngine, const CrackFactoryParams & _params) const;

		DataLayer::IFileRepository * fileRepository;
	};
}