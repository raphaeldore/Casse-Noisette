#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace DataLayer;

// À décommenter pour tester avec un gros dictionnaire (attention, il faut beaucoup de RAM!)
//#define TEST_LARGE_DICTIONARY

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
			catch (runtime_error) {
				error_thrown = true;
			}
			//Assert
			Assert::IsTrue(error_thrown);
		}

		TEST_METHOD(loadPasswordFile_put_the_password_in_multimap_in_the_hashedPasswordVector)
		{
			//Arrange
			multimap<string, string> expectedMap;
			string userName = "no_user";

			expectedMap.insert(make_pair(userName, "f71dbe52628a3f83a77ab494817525c6"));
			expectedMap.insert(make_pair(userName, "49d02d55ad10973b7b9d0dc9eba7fdf0"));
			expectedMap.insert(make_pair(userName, "5d933eef19aee7da192608de61b6c23d"));
			expectedMap.insert(make_pair(userName, "2db313fabca57504d9dc776e46b304f6"));
			expectedMap.insert(make_pair(userName, "bdb8c008fa551ba75f8481963f2201da"));

			//Action
			fileRepository->loadPasswordFile(file_name_no_separator);
			multimap<string, string> actualMap = fileRepository->getAllHashedPasswords();

			// Assert
			Assert::IsTrue(expectedMap == actualMap);
		}

		TEST_METHOD(hashed_Password_multimap_has_the_same_number_of_password_than_the_file)
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
			catch (logic_error){
				exception_thrown = true;
			}
			//Assert
			Assert::IsTrue(exception_thrown);
		}

		TEST_METHOD(open_file_with_separator_and_one_line_should_create_multimap_with_the_user_an_hashed_password)
		{
			//Arrange
			string file = "../TestsFIles/simple_password_separator.txt";
			multimap<string, string> EXPECTED_MAP;
			EXPECTED_MAP.insert(make_pair("user1", "6d4db5ff0c117864a02827bad3c361b9"));

			//Action
			fileRepository->loadPasswordFile(file);
			multimap<string, string> ACTUAL_MAP = fileRepository->getAllHashedPasswords();

			//Assert
			Assert::IsTrue(EXPECTED_MAP == ACTUAL_MAP);
		}

		TEST_METHOD(open_empty_file_with_separator_specified_should_return_a_logic_error)
		{
			//Arrange
			bool exception_thrown = false;

			//Action
			try
			{
				fileRepository->loadPasswordFile(emptyFile, ";");
			}
			catch (logic_error)
			{
				exception_thrown = true;
			}

			//Assert
			Assert::IsTrue(exception_thrown);
		}

		TEST_METHOD(open_file_with_separator_and_multi_line_should_create_multimap_with_the_user_an_hashed_password_and_empty_string)
		{
			//Arrange
			multimap<string, string> EXPECTED_MAP;
			EXPECTED_MAP.insert(make_pair("user1", "f71dbe52628a3f83a77ab494817525c6"));
			EXPECTED_MAP.insert(make_pair("user2", "49d02d55ad10973b7b9d0dc9eba7fdf0"));
			EXPECTED_MAP.insert(make_pair("user3", "5d933eef19aee7da192608de61b6c23d"));
			EXPECTED_MAP.insert(make_pair("user4", "2db313fabca57504d9dc776e46b304f6"));
			EXPECTED_MAP.insert(make_pair("user5", "bdb8c008fa551ba75f8481963f2201da"));

			//Action
			fileRepository->loadPasswordFile(file_name_with_separator);

			auto ACTUAL_MAP = fileRepository->getAllHashedPasswords();

			// Assert
			Assert::IsTrue(EXPECTED_MAP == ACTUAL_MAP);
		}

		TEST_METHOD(open_file_with_a_multiple_character_seperator_should_create_a_multimap_with_the_user_an_hashed_password_and_empty_string)
		{
			// Arrange
			string file = "../TestsFIles/simple_password_multichar_separator.txt";
			multimap<string, string> EXPECTED_MAP;
			EXPECTED_MAP.insert(make_pair("user1", "6d4db5ff0c117864a02827bad3c361b9"));

			//Action
			fileRepository->loadPasswordFile(file, "!!");
			multimap<string, string> ACTUAL_MAP = fileRepository->getAllHashedPasswords();

			//Assert
			Assert::IsTrue(EXPECTED_MAP == ACTUAL_MAP);
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


		//////////////////////////////////////// LoadDictionary ////////////////////////////////////////

		TEST_METHOD(load_dictionary_file_returns_all_words_in_the_dictionary)
		{
			// Arrange
			string dictionaryPath = "../TestsFiles/Dictionaries/small_dict.txt";
			unsigned int EXPECTED_DICTIONARY_SIZE = 4;
			vector<string> EXPECTED_DICTIONARY {
				"a",
				"b",
				"c",
				"patate"
			};

			// Action
			vector<string> ACTUAL_DICTIONARY = fileRepository->loadDictionaryFile(dictionaryPath);

			// Assert
			Assert::AreEqual(EXPECTED_DICTIONARY_SIZE, ACTUAL_DICTIONARY.size());
			Assert::IsTrue(EXPECTED_DICTIONARY == ACTUAL_DICTIONARY);
		}

		TEST_METHOD(load_dictionary_throws_runtime_exception_when_file_does_not_exist)
		{
			// Arrange
			auto loadDictionaryWithNonExistantFileFunction = [this] {fileRepository->loadDictionaryFile("this_file_does_not_exist"); };

			// Assert
			Assert::ExpectException<runtime_error>(loadDictionaryWithNonExistantFileFunction);
		}

		TEST_METHOD(load_dictionary_throws_runtime_exception_when_file_is_empty)
		{
			// Arrange
			auto loadDictionaryWithEmptyFileFunction = [this] {fileRepository->loadDictionaryFile("../TestsFiles/Dictionaries/empty_dict.txt"); };

			// Assert
			Assert::ExpectException<runtime_error>(loadDictionaryWithEmptyFileFunction);
		}

#ifdef TEST_LARGE_DICTIONARY

		TEST_METHOD(load_dictionary_file_works_with_large_files)
		{
			/********************************************
			* NOTE: Vous devez décompresser le fichier  *
			*    TestsFiles/Dictionaries/rockyou.7z     *
			* Pour que ce test fonctionne			    *
			*                                           *
			********************************************/
			// Arrange
			string dictionaryPath = "../TestsFiles/Dictionaries/rockyou.txt";
			//unsigned int EXPECTED_DICTIONARY_SIZE = 4;
			vector<string> FIRST_FIVE_WORDS{
				"123456",
				"12345",
				"123456789",
				"password",
				"iloveyou"
			};

			vector<string> RANDOM_WORDS_IN_FILE {
				"lilb83",
				"jacoby2003",
				"s9901856i",
				"karencita17",
				"1002456"
			};

			// Action
			string exceptionMsg;
			vector<string> ACTUAL_DICTIONARY;
			unsigned int actual_dictionary_size;
			try
			{
				ACTUAL_DICTIONARY = fileRepository->loadDictionaryFile(dictionaryPath);
				actual_dictionary_size = ACTUAL_DICTIONARY.size();
			} catch (exception ex)
			{
				exceptionMsg = ex.what();
			}
			

			// Assert
			//Assert::AreEqual(EXPECTED_DICTIONARY_SIZE, ACTUAL_DICTIONARY.size());
			//Assert::IsTrue(EXPECTED_DICTIONARY == ACTUAL_DICTIONARY);
		}
#endif

	};
}