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
		string file_name = "../TestsFIles/hashed_password_test.txt";

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
			string fileNameNotExists = "not_exits.txt";
			bool error_thrown = false;
			//Action
			try
			{
				fileRepository->loadPasswordFile(fileNameNotExists);
			}
			catch(runtime_error) {
				error_thrown = true;
			}
			//Assert
			Assert::IsTrue(error_thrown);
		}

		TEST_METHOD(loadPasswordFile_put_the_password_in_the_hashedPasswordVector)
		{
			//Arrange
			const string FILE_LINE_1 = "f71dbe52628a3f83a77ab494817525c6";
			const string FILE_LINE_2 = "49d02d55ad10973b7b9d0dc9eba7fdf0";
			const string FILE_LINE_3 = "5d933eef19aee7da192608de61b6c23d";
			const string FILE_LINE_4 = "2db313fabca57504d9dc776e46b304f6";
			const string FILE_LINE_5 = "bdb8c008fa551ba75f8481963f2201da";
			//Action
			fileRepository->loadPasswordFile(file_name);

			string vectorLine_1 = fileRepository->getAllHashedPasswords()[0];
			string vectorLine_2 = fileRepository->getAllHashedPasswords()[1];
			string vectorLine_3 = fileRepository->getAllHashedPasswords()[2];
			string vectorLine_4 = fileRepository->getAllHashedPasswords()[3];
			string vectorLine_5 = fileRepository->getAllHashedPasswords()[4];
			//Assert
			Assert::AreEqual(FILE_LINE_1, vectorLine_1);
			Assert::AreEqual(FILE_LINE_2, vectorLine_2);
			Assert::AreEqual(FILE_LINE_3, vectorLine_3);
			Assert::AreEqual(FILE_LINE_4, vectorLine_4);
			Assert::AreEqual(FILE_LINE_5, vectorLine_5);
		}

		TEST_METHOD(hashed_Password_Vector_has_the_same_number_of_password_than_the_file)
		{
			//Arrange
			const int NBR_PASSWORD_IN_FILE = 5;
			fileRepository->loadPasswordFile(file_name);
			//Action
			int hashedPwdVectorSize = fileRepository->getAllHashedPasswords().size();
			//Assert
			Assert::AreEqual(NBR_PASSWORD_IN_FILE, hashedPwdVectorSize);
		}

		TEST_METHOD(if_file_is_empty_return_an_logic_error)
		{
			//Arrange
			bool exception_thrown = false;
			//Action
			try
			{
				fileRepository->loadPasswordFile("../TestsFiles/emptyFile.txt");
			}
			catch(logic_error){
				exception_thrown = true;
			}
			//Assert
			Assert::IsTrue(exception_thrown);
		}

	};
}