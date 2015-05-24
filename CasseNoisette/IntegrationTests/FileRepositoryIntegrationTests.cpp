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
		string file_name_no_separator = "..\\TestsFiles\\hashed_password_test.txt";
		string file_name_with_separator = "..\\TestsFiles\\hashed_password_separator_test.txt";
		string emptyFile = "..\\TestsFiles\\emptyFile.txt";

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

			expectedMap.insert(make_pair("f71dbe52628a3f83a77ab494817525c6", userName));
			expectedMap.insert(make_pair("49d02d55ad10973b7b9d0dc9eba7fdf0", userName));
			expectedMap.insert(make_pair("5d933eef19aee7da192608de61b6c23d", userName));
			expectedMap.insert(make_pair("2db313fabca57504d9dc776e46b304f6", userName));
			expectedMap.insert(make_pair("bdb8c008fa551ba75f8481963f2201da", userName));

			//Action
			multimap<string, string> actualMap = fileRepository->loadPasswordFile(file_name_no_separator);;

			// Assert
			Assert::IsTrue(expectedMap == actualMap);
		}

		TEST_METHOD(hashed_Password_multimap_has_the_same_number_of_password_than_the_file)
		{
			//Arrange
			const int NBR_PASSWORD_IN_FILE = 5;

			//Action
			auto passwordsFile = fileRepository->loadPasswordFile(file_name_no_separator);
			int hashedPwdVectorSize = passwordsFile.size();

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
			catch (runtime_error err){
				exception_thrown = true;
			}
			//Assert
			Assert::IsTrue(exception_thrown);
		}

		TEST_METHOD(open_file_with_separator_and_one_line_should_create_multimap_with_the_user_an_hashed_password)
		{
			//Arrange
			string file = "..\\TestsFiles\\simple_password_separator.txt";
			multimap<string, string> EXPECTED_MAP;
			EXPECTED_MAP.insert(make_pair("6d4db5ff0c117864a02827bad3c361b9", "user1"));

			//Action
			multimap<string, string> ACTUAL_MAP = fileRepository->loadPasswordFile(file);

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
			catch (runtime_error)
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
			EXPECTED_MAP.insert(make_pair("f71dbe52628a3f83a77ab494817525c6", "user1"));
			EXPECTED_MAP.insert(make_pair("49d02d55ad10973b7b9d0dc9eba7fdf0", "user2"));
			EXPECTED_MAP.insert(make_pair("5d933eef19aee7da192608de61b6c23d", "user3"));
			EXPECTED_MAP.insert(make_pair("2db313fabca57504d9dc776e46b304f6", "user4"));
			EXPECTED_MAP.insert(make_pair("bdb8c008fa551ba75f8481963f2201da", "user5"));

			//Action
			auto ACTUAL_MAP = fileRepository->loadPasswordFile(file_name_with_separator);

			// Assert
			Assert::IsTrue(EXPECTED_MAP == ACTUAL_MAP);
		}

		TEST_METHOD(open_file_with_a_multiple_character_seperator_should_create_a_multimap_with_the_user_an_hashed_password_and_empty_string)
		{
			// Arrange
			string file = "..\\TestsFiles\\simple_password_multichar_separator.txt";
			multimap<string, string> EXPECTED_MAP;
			EXPECTED_MAP.insert(make_pair("6d4db5ff0c117864a02827bad3c361b9", "user1"));

			//Action
			multimap<string, string> ACTUAL_MAP = fileRepository->loadPasswordFile(file, "!!");

			//Assert
			Assert::IsTrue(EXPECTED_MAP == ACTUAL_MAP);
		}

		TEST_METHOD(file_with_more_than_one_separator_per_line_return_invalid_argument)
		{
			//Arrange
			string file = "..\\TestsFiles\\invalid_separator_file.txt";
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


		TEST_METHOD(loadPasswordFile_throws_exception_when_non_empty_file_exists_but_unable_to_open_it)
		{
			// Si le fichier existe, et n'est pas vide, mais qu'on est incapable d'ouvrir le fichier
			// pour une raison quelconque, on lance une exception. Dans ce test, nous empêchons
			// la lecture du fichier en enlevant la permission aux utilisateurs de lire le fichier
			// lockedFile.txt

			// Action

			// Script qui empêche la lecture du fichier par tous les utilisateurs
			system("..\\Scripts\\lockFile.bat");

			auto loadLockedFileFunction = [this] {fileRepository->loadPasswordFile("..\\TestsFiles\\Other\\lockedFile.txt"); };

			// Assert
			Assert::ExpectException<runtime_error>(loadLockedFileFunction);

			// Script qui redonne permission à tout le monde de lire le fichier
			// (sinon git ne veut rien savoir)
			system("..\\Scripts\\unlockFile.bat");
		}


		//////////////////////////////////////// LoadDictionary ////////////////////////////////////////

		TEST_METHOD(load_dictionary_file_returns_all_words_in_the_dictionary)
		{
			// Arrange
			string dictionaryPath = "..\\TestsFiles\\Dictionaries\\small_dict.txt";
			unsigned int EXPECTED_DICTIONARY_SIZE = 4;
			queue<string> EXPECTED_DICTIONARY;
			EXPECTED_DICTIONARY.push("a");
			EXPECTED_DICTIONARY.push("b");
			EXPECTED_DICTIONARY.push("c");
			EXPECTED_DICTIONARY.push("patate");

			// Action
			auto ACTUAL_DICTIONARY = fileRepository->loadDictionaryFile(dictionaryPath);

			// Assert
			Assert::AreEqual(EXPECTED_DICTIONARY_SIZE, ACTUAL_DICTIONARY->size());
			Assert::IsTrue(EXPECTED_DICTIONARY == *ACTUAL_DICTIONARY);
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
			auto loadDictionaryWithEmptyFileFunction = [this] {fileRepository->loadDictionaryFile("..\\TestsFiles\\Dictionaries\\empty_dict.txt"); };

			// Assert
			Assert::ExpectException<runtime_error>(loadDictionaryWithEmptyFileFunction);
		}

		TEST_METHOD(loadDictionaryFile_throws_exception_when_non_empty_file_exists_but_unable_to_open_it)
		{
			// Même chose que le test ci-haut 
			//     loadPasswordFile_throws_exception_when_non_empty_file_exists_but_unable_to_open_it


			// Action
			system("..\\Scripts\\lockFile.bat");

			auto loadLockedFileFunction = [this] {fileRepository->loadDictionaryFile("..\\TestsFiles\\Other\\lockedFile.txt"); };

			// Assert
			Assert::ExpectException<runtime_error>(loadLockedFileFunction);

			system("..\\Scripts\\unlockFile.bat");
		}

#ifdef TEST_LARGE_DICTIONARY

		TEST_METHOD(load_dictionary_file_works_with_large_files)
		{
			// Arrange
			string dictionaryPath = "..\\TestsFiles\\Dictionaries\\cain.txt";
			unsigned int EXPECTED_DICTIONARY_SIZE = 306706U;

			string EXPECTED_DICT_FRONT = "!@#$%";
			string EXPECTED_DICT_BACK = "zyzzogeton";

			// Action
			unique_ptr<queue<string>> ACTUAL_DICTIONARY = fileRepository->loadDictionaryFile(dictionaryPath);
			unsigned int actual_dictionary_size = ACTUAL_DICTIONARY->size();

			// Assert
			Assert::AreEqual(EXPECTED_DICTIONARY_SIZE, actual_dictionary_size);
			Assert::AreEqual(EXPECTED_DICT_FRONT, ACTUAL_DICTIONARY->front());
			Assert::AreEqual(EXPECTED_DICT_BACK, ACTUAL_DICTIONARY->back());
		}

		TEST_METHOD(load_dictionary_file_works_with_very_large_files)
		{
			/********************************************
			* NOTE: Vous devez décompresser le fichier  *
			*    TestsFiles/Dictionaries/rockyou.7z     *
			* Pour que ce test fonctionne			    *
			*                                           *
			********************************************/
			
			// Arrange
			string dictionaryPath = "..\\TestsFiles\\Dictionaries\\rockyou.txt";
			unsigned int EXPECTED_DICTIONARY_SIZE = 9999998U;

			string EXPECTED_DICT_FRONT = "123456";
			string EXPECTED_DICT_BACK = "arisha786";

			// Action
			unique_ptr<queue<string>> ACTUAL_DICTIONARY = fileRepository->loadDictionaryFile(dictionaryPath);
			unsigned int actual_dictionary_size = ACTUAL_DICTIONARY->size();

			// Assert
			Assert::AreEqual(EXPECTED_DICTIONARY_SIZE, actual_dictionary_size);
			Assert::AreEqual(EXPECTED_DICT_FRONT, ACTUAL_DICTIONARY->front());
			Assert::AreEqual(EXPECTED_DICT_BACK, ACTUAL_DICTIONARY->back());
		}
#endif

	};
}