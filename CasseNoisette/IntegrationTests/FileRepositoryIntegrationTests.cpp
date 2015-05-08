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
		string file_name_no_separator = "../TestsFIles/hashed_password_test.txt";
		string file_name_with_separator = "../TestsFIles/hashed_password_separator_test.txt";
		string emptyFile = "../TestsFiles/emptyFile.txt";

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

		TEST_METHOD(loadPasswordFile_put_the_password_in_tuple_in_the_hashedPasswordVector)
		{
			//Arrange
			const tuple<string, string, string> EXPECT_TUPLE_0{ "no_user", "f71dbe52628a3f83a77ab494817525c6", "" };
			const tuple<string, string, string> EXPECT_TUPLE_1{ "no_user", "49d02d55ad10973b7b9d0dc9eba7fdf0", "" };
			const tuple<string, string, string> EXPECT_TUPLE_2{ "no_user", "5d933eef19aee7da192608de61b6c23d", "" };
			const tuple<string, string, string> EXPECT_TUPLE_3{ "no_user", "2db313fabca57504d9dc776e46b304f6", "" };
			const tuple<string, string, string> EXPECT_TUPLE_4{ "no_user", "bdb8c008fa551ba75f8481963f2201da", "" };
			//Action
			fileRepository->loadPasswordFile(file_name_no_separator);

			tuple<string, string, string> result_tuple_0 = fileRepository->getAllHashedPasswords()[0];
			tuple<string, string, string> result_tuple_1 = fileRepository->getAllHashedPasswords()[1];
			tuple<string, string, string> result_tuple_2 = fileRepository->getAllHashedPasswords()[2];
			tuple<string, string, string> result_tuple_3 = fileRepository->getAllHashedPasswords()[3];
			tuple<string, string, string> result_tuple_4 = fileRepository->getAllHashedPasswords()[4];
			//Assert
			//Assert::AreEqual(EXPECT_TUPLE_0, result_tuple_0);
			//Assert::AreEqual(EXPECT_TUPLE_1, result_tuple_1);
			//Assert::AreEqual(EXPECT_TUPLE_2, result_tuple_2);
			//Assert::AreEqual(EXPECT_TUPLE_3, result_tuple_3);
			//Assert::AreEqual(EXPECT_TUPLE_4, result_tuple_4);

			Assert::IsTrue(tuples_are_equal(EXPECT_TUPLE_0, result_tuple_0));
		}

		TEST_METHOD(hashed_Password_Vector_has_the_same_number_of_password_than_the_file)
		{
			//Arrange
			const int NBR_PASSWORD_IN_FILE = 5;
			fileRepository->loadPasswordFile(file_name_no_separator);
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
				fileRepository->loadPasswordFile(emptyFile);
			}
			catch(logic_error){
				exception_thrown = true;
			}
			//Assert
			Assert::IsTrue(exception_thrown);
		}

		TEST_METHOD(if_separator_specified_and_no_separator_in_file_throw_invalid_argument)
		{
			//Arrange
			bool exception_thrown = false;
			//Action
			try
			{
				fileRepository->loadPasswordFile(file_name_no_separator);
			}
			catch (invalid_argument) {
				exception_thrown = true;
			}
			//Assert
			Assert::IsTrue(exception_thrown);
		}

		TEST_METHOD(open_file_with_separator_and_one_line_should_create_a_vector_of_tuple_with_the_user_an_hashed_password_and_empty_string)
		{
			//Arrange
			string file = "../TestsFIles/simple_password_separator.txt";
			const tuple<string, string, string> ATTEMPT_TUPLE {"user1", "6d4db5ff0c117864a02827bad3c361b9", ""};
			//Action
			fileRepository->loadPasswordFile(file);
			vector<tuple<string, string, string>> result_vector = fileRepository->getAllHashedPasswords();
			//Assert
			//Assert::AreEqual(ATTEMPT_TUPLE, result_vector[0]);
		}

		TEST_METHOD(open_empty_file_with_separator_specified_should_return_an_runtime_error)
		{
			//Arrange
			bool exception_thrown = false;
			//Action
			try
			{
				fileRepository->loadPasswordFile(emptyFile, ";");
			}
			catch (runtime_error)
			{
				exception_thrown = true;
			}
			//Assert
			Assert::IsTrue(exception_thrown);
		}

		TEST_METHOD(open_file_with_separator_and_multi_line_should_create_a_vector_of_tuple_with_the_user_an_hashed_password_and_empty_string)
		{
			//Arrange
			const tuple<string, string, string> EXPECT_TUPLE_0{ "user1", "f71dbe52628a3f83a77ab494817525c6", "" };
			const tuple<string, string, string> EXPECT_TUPLE_1{ "user2", "49d02d55ad10973b7b9d0dc9eba7fdf0", "" };
			const tuple<string, string, string> EXPECT_TUPLE_2{ "user3", "5d933eef19aee7da192608de61b6c23d", "" };
			const tuple<string, string, string> EXPECT_TUPLE_3{ "user4", "2db313fabca57504d9dc776e46b304f6", "" };
			const tuple<string, string, string> EXPECT_TUPLE_4{ "user5", "bdb8c008fa551ba75f8481963f2201da", "" };
			//Action
			fileRepository->loadPasswordFile(file_name_with_separator);

			tuple<string, string, string> result_tuple_0 = fileRepository->getAllHashedPasswords()[0];
			tuple<string, string, string> result_tuple_1 = fileRepository->getAllHashedPasswords()[1];
			tuple<string, string, string> result_tuple_2 = fileRepository->getAllHashedPasswords()[2];
			tuple<string, string, string> result_tuple_3 = fileRepository->getAllHashedPasswords()[3];
			tuple<string, string, string> result_tuple_4 = fileRepository->getAllHashedPasswords()[4];
			//Assert
			//Assert::AreEqual(EXPECT_TUPLE_0, result_tuple_0);
			//Assert::AreEqual(EXPECT_TUPLE_1, result_tuple_1);
			//Assert::AreEqual(EXPECT_TUPLE_2, result_tuple_2);
			//Assert::AreEqual(EXPECT_TUPLE_3, result_tuple_3);
			//Assert::AreEqual(EXPECT_TUPLE_4, result_tuple_4);
		}

		TEST_METHOD(file_with_more_than_one_separator_per_line_return_invalid_argument)
		{
			//Arrange
			string file = "../TestsFiles/invalid_separator_file.txt";
			bool exception_thrown = false;
			//Action
			try
			{
				fileRepository->loadPasswordFile(file);
			}
			catch (invalid_argument)
			{
				exception_thrown = true;
			}
			//Assert
			Assert::IsTrue(exception_thrown);
		}

		bool tuples_are_equal(const tuple<string, string, string> expected, const tuple<string, string, string> actual)
		{
			return expected == actual;
		}
	};


}