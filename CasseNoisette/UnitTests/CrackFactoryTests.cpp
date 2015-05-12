#include "stdafx.h"

#pragma warning(push)
#pragma warning(disable: 4800)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace CrackEngine;

namespace UnitTests
{
	TEST_CLASS(CrackFactory)
	{
	public:
		CrackEngine::CrackFactory * crackFactory;
		unique_ptr<CrackEngine::CrackFactoryParams> crackFactoryParams;
		unique_ptr<set<Parameter>> parameters;
		unique_ptr<FakeFileRepository> fakeFileRepository;

		TEST_METHOD_INITIALIZE(CrackEngineParams_Initialize)
		{
			fakeFileRepository = make_unique<FakeFileRepository>();
			crackFactory = CrackEngine::CrackFactory::GetCrackFactory();
			crackFactory->SetFileRepository(*fakeFileRepository);
			crackFactoryParams = make_unique<CrackEngine::CrackFactoryParams>();
			parameters = make_unique<set<Parameter>>();
			parameters->insert(Parameter(PARAM_TYPE::PWD_FILE_PATH, "fakePasswordFile.txt"));
			parameters->insert(Parameter(PARAM_TYPE::SEPERATOR, ":"));
			parameters->insert(Parameter(PARAM_TYPE::RESULTS_FILE_PATH, "/home/rdore/cracking_results.txt"));
			parameters->insert(Parameter(PARAM_TYPE::HASH_TYPE, "MD5"));
		}

		TEST_METHOD(CreateCrackEngine_can_create_brute_force_engine)
		{
			// Arrange
			parameters->insert(Parameter(PARAM_TYPE::CHARSET, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_+="));
			parameters->insert(Parameter(PARAM_TYPE::MAX_PWD_LENGTH, "6"));
			crackFactoryParams->setParameters(*parameters);

			// Action
			unique_ptr<CrackEngine::ICrackEngine> crackEngine = crackFactory->CreateCrackEngine(BRUTE_FORCE, *crackFactoryParams);

			// Assert
			Assert::IsTrue(fakeFileRepository->hasLoadPasswordFileBeenCalled());
			Assert::IsTrue(dynamic_cast<BruteForce *>(crackEngine.get()));
		}

		TEST_METHOD(CreateCrackEngine_can_create_dictionary_engine)
		{
			// Arrange
			parameters->insert(Parameter(PARAM_TYPE::DICTIONARY_PATH, "randomDictionary.txt"));
			crackFactoryParams->setParameters(*parameters);

			// Action
			unique_ptr<CrackEngine::ICrackEngine> crackEngine = crackFactory->CreateCrackEngine(DICTIONARY, *crackFactoryParams);

			// Assert
			Assert::IsTrue(fakeFileRepository->hasLoadPasswordFileBeenCalled());
			Assert::IsTrue(fakeFileRepository->hasLoadDictionaryFileBeenCalled());
			Assert::IsTrue(dynamic_cast<Dictionary *>(crackEngine.get()));
		}
	};
}

#pragma warning(pop)