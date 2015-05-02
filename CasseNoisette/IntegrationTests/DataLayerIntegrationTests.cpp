#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace DataLayer;

namespace IntegrationTests
{		
	TEST_CLASS(FileRepositoryIntegrationTests)
	{
	public:
		FileRepository * fileRepository;
		TEST_METHOD_INITIALIZE(FileRepositoryIntegrationTests_Initialize)
		{
			fileRepository = new FileRepository;
		}

		TEST_METHOD_CLEANUP(FileRepositoryIntegrationTests_CleanUP)
		{
			delete fileRepository;
		}
		
		TEST_METHOD(when_load_file_if_file_not_exists_throw_runtime_error_exception)
		{
			//Arrange
			string file_name = "not_exits.txt";
			bool error_thrown = false;
			//Action
			try
			{
				fileRepository->loadPasswordFile(file_name);
			}
			catch(runtime_error) {
				error_thrown = true;
			}
			//Assert
			Assert::IsTrue(error_thrown);
		}

	};
}