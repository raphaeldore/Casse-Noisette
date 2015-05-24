#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTests
{
	TEST_CLASS(FileUtilitiesTests){

		TEST_METHOD(getFileContent_returns_all_content_in_the_file)
		{
			// Arrange
			string filePath = "..\\TestsFiles\\UtilitiesTests\\fileToRead.txt";
			string EXPECTED_CONTENT = "Bonjour, je m'appelle Jean.\n\nJ'aime les patates.";

			// Action
			string ACTUAL_CONTENT = Utilities::FileUtilities::GetFileContent(filePath);

			// Assert
			Assert::AreEqual(EXPECTED_CONTENT, ACTUAL_CONTENT);
		}

		TEST_METHOD(getFileContent_throws_runtime_error_if_file_does_not_exist)
		{
			// Arrange
			auto loadDictionaryWithNonExistantFileFunction = [this] {Utilities::FileUtilities::GetFileContent("this_file_does_not_exist"); };

			// Assert
			Assert::ExpectException<runtime_error>(loadDictionaryWithNonExistantFileFunction);
		}

		TEST_METHOD(getFileContent_throws_runtime_error_if_unable_to_open_file)
		{
			// Script empêche la lecture du fichier par tous les utilisateurs
			system("..\\Scripts\\lockFile.bat");

			// On tente donc d'ouvrir un fichier qu'on a pas la permission d'ouvrir
			auto loadDictionaryLockedFileFunction = [this] {Utilities::FileUtilities::GetFileContent("..\\TestsFiles\\Other\\lockedFile.txt"); };

			// Assert
			Assert::ExpectException<runtime_error>(loadDictionaryLockedFileFunction);

			// Script qui redonne permission à tout le monde de lire le fichier
			// (sinon git ne veut rien savoir)
			system("..\\Scripts\\unlockFile.bat");
		}
		
		TEST_METHOD(does_file_exist_returns_false_if_file_does_not_exist) {
			// Arrange
			string nonExistantFile = "patate.txt";
			
			// Action et Assert
			Assert::IsFalse(Utilities::FileUtilities::DoesFileExist(nonExistantFile));
		}

		TEST_METHOD(does_file_exist_returns_true_if_file_exists) {
			// Arrange
			string existingFilePath = "..\\TestsFiles\\simple_password.txt";

			// Action et Assert
			Assert::IsTrue(Utilities::FileUtilities::DoesFileExist(existingFilePath));
		}

		TEST_METHOD(IsFileEmpty_returns_true_if_empty) {
			// Arrange
			string emptyFilePath = "..\\TestsFiles\\emptyFile.txt";

			// Action et Assert
			Assert::IsTrue(Utilities::FileUtilities::IsFileEmpty(emptyFilePath));
		}

		TEST_METHOD(IsFileEmpty_returns_flase_if_not_empty) {
			// Arrange
			string nonEmptyFilePath = "..\\TestsFiles\\simple_password.txt";

			// Action et Assert
			Assert::IsFalse(Utilities::FileUtilities::IsFileEmpty(nonEmptyFilePath));
		}

		/**********
		
		NOTE: À partir de maintenant, je considère que les fonctions DoesFileExist et IsFileEmpty 
		      sont fonctionnelles (Et donc je les utilises dans les Asserts).
		
		*********/

		TEST_METHOD(getFileNameFromPath_returns_correct_fileName)
		{
			// Arrange
			string fullPath = "C:\\Users\\MySuperSecretFiles\\supersecrets.txt";
			string EXPECTED_FILE_NAME = "supersecrets.txt";

			// Action
			string ACTUAL_FILE_NAME = Utilities::FileUtilities::GetFileNameFromPath(fullPath);

			// Assert
			Assert::AreEqual(EXPECTED_FILE_NAME, ACTUAL_FILE_NAME);
		}

		TEST_METHOD(GetBaseFileNameFromPath_returns_fileName_without_extension)
		{
			// Arrange
			string fullPath = "C:\\Users\\MySuperSecretFiles\\supersecrets.txt";
			string EXPECTED_FILE_NAME = "supersecrets";

			// Action
			string ACTUAL_FILE_NAME = Utilities::FileUtilities::GetBaseFileNameFromPath(fullPath);

			// Assert
			Assert::AreEqual(EXPECTED_FILE_NAME, ACTUAL_FILE_NAME);
		}

		TEST_METHOD(GetFileExtension_returns_file_extension)
		{
			// Arrange
			string fakeFileName = "supersecrets.awesome";
			string EXPECTED_EXTENSION = "awesome";

			// Action
			string ACTUAL_EXTENSION = Utilities::FileUtilities::GetFileExtension(fakeFileName);
			// Assert

			Assert::AreEqual(EXPECTED_EXTENSION, ACTUAL_EXTENSION);
		}

		TEST_METHOD(IncrementFileNameIfExists_returns_correct_incremented_file_name)
		{
			// Note: Dans le dossier '..\TestsFiles\\UtilitiesTests\' il y a, parmis d'autres fichiers,
			// les fichiers suivants: file.txt, file1.txt, et file2.txt. Je me base sur ça pour faire ce test.

			// Arrange
			string attemptedPath = "..\\TestsFiles\\UtilitiesTests\\file.txt";
			string EXPECTED_INCREMENTED_FILE_NAME = "..\\TestsFiles\\UtilitiesTests\\file3.txt";

			// Action
			string ACTUAL_INCREMENTED_FILE_NAME = Utilities::FileUtilities::IncrementFileNameIfExists(attemptedPath);

			// Assert
			Assert::AreEqual(EXPECTED_INCREMENTED_FILE_NAME, ACTUAL_INCREMENTED_FILE_NAME);
		}

		TEST_METHOD(IncrementFileNameIfExists_returns_original_path_if_fileName_does_not_exist)
		{
			// Arrange
			string attemptedPath = "..\\TestsFiles\\UtilitiesTests\\thisFileDoesNotExist.txt";
			string EXPECTED_INCREMENTED_FILE_NAME = "..\\TestsFiles\\UtilitiesTests\\thisFileDoesNotExist.txt";

			// Action
			string ACTUAL_INCREMENTED_FILE_NAME = Utilities::FileUtilities::IncrementFileNameIfExists(attemptedPath);

			// Assert
			Assert::AreEqual(EXPECTED_INCREMENTED_FILE_NAME, ACTUAL_INCREMENTED_FILE_NAME);
		}

		TEST_METHOD(clearFileContent_empties_the_file)
		{
			// Arrange
			string fileToClear = "..\\TestsFiles\\UtilitiesTests\\fileToClear.txt";

			/// On ajoute du contenu au fichier (pour qu'il ne soit plus vide)
			ofstream file(fileToClear, ofstream::out);
			file << "Bonjour";
			file.close();

			/// On s'assure qu'on a bien écrit dans le fichier
			Assert::IsFalse(Utilities::FileUtilities::IsFileEmpty(fileToClear));

			// Action
			Utilities::FileUtilities::ClearFileContent(fileToClear);

			// Assert
			Assert::IsTrue(Utilities::FileUtilities::IsFileEmpty(fileToClear));
		}

		TEST_METHOD(clearFileContent_throws_runtime_exception_if_file_does_not_exist)
		{
			// Arrange
			auto loadDictionaryWithNonExistantFileFunction = [this] {Utilities::FileUtilities::ClearFileContent("this_file_does_not_exist"); };

			// Assert
			Assert::ExpectException<runtime_error>(loadDictionaryWithNonExistantFileFunction);
		}

		//TEST_METHOD(generate_dictionary) {
		//	Utilities::DictionaryGenerator generator(8, "abcdefg", "words.txt");
		//	generator.GenerateDictionary();
		//}


	};

}