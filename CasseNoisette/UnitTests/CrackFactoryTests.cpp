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
		TEST_METHOD_INITIALIZE(CrackEngineParams_Initialize)
		{
			crackFactory = CrackEngine::CrackFactory::GetCrackFactory();
			crackFactoryParams = make_unique<CrackEngine::CrackFactoryParams>();
		}

		TEST_METHOD(CreateCrackEngine_can_create_brute_force_engine)
		{
			// Arrange
			set<Parameter> parameters;
			parameters.insert(Parameter(PARAM_TYPE::PWD_FILE_PATH, "/home/rdore/passwords.txt"));
			parameters.insert(Parameter(PARAM_TYPE::RESULTS_FILE_PATH, "/home/rdore/cracking_results.txt"));
			parameters.insert(Parameter(PARAM_TYPE::CHARSET, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_+="));
			parameters.insert(Parameter(HASH_TYPE, "MD5"));
			parameters.insert(Parameter(MAX_PWD_LENGTH, "6"));
			crackFactoryParams->setParameters(parameters);

			// Action
			unique_ptr<CrackEngine::ICrackEngine> crackEngine = crackFactory->CreateCrackEngine(BRUTE_FORCE, *crackFactoryParams);

			// Assert
			Assert::IsTrue(dynamic_cast<BruteForce *>(crackEngine.get()));
		}

	};
}

#pragma warning(pop)