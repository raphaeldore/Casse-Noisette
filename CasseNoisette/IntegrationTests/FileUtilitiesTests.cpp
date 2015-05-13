#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTests
{
	TEST_CLASS(Utilities_tests){
		TEST_METHOD(does_file_exist_returns_false_if_file_does_not_exist) {
			Assert::IsFalse(Utilities::FileUtilities::DoesFileExist("patate.txt"));
		}

		TEST_METHOD(does_file_exist_returns_true_if_file_exists) {
			Assert::IsTrue(Utilities::FileUtilities::DoesFileExist("../TestsFiles/simple_password.txt"));
		}

		//TEST_METHOD(can_create_file) {
		//	Assert::IsTrue(Utilities::FileUtilities::CreateFile("E:\\bybye.txt"));
		//}

		TEST_METHOD(IsFileEmpty_returns_true_if_empty) {
			Assert::IsTrue(Utilities::FileUtilities::IsFileEmpty("../TestsFiles/emptyFile.txt"));
		}

		TEST_METHOD(IsFileEmpty_returns_flase_if_not_empty) {
			Assert::IsFalse(Utilities::FileUtilities::IsFileEmpty("../TestsFiles/simple_password.txt"));
		}

		TEST_METHOD(can_create_file_from_vector) {
			vector <string> words{ "Hello", "my", "name", "is", "slim", "shady" };
			Utilities::FileUtilities::AppendVectorContentToFile("words.txt", words);
		}

		//TEST_METHOD(generate_dictionary) {
		//	Utilities::DictionaryGenerator generator(4, "abcdefghijklmnopqrstuvwxyz", "words.txt");
		//	generator.GenerateDictionary();
		//}
	};
}