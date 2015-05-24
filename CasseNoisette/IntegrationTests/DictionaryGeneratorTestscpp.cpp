#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTests
{
	TEST_CLASS(DictionaryGeneratorTests){
		TEST_METHOD(GenerateDictionary_generates_dictionary) {
			
			// Arrange
			vector<string> EXPECTED_DICTIONARY_FILE_WORDS { "a",
				"b",
				"c",
				"aa",
				"ab",
				"ac",
				"ba",
				"bb",
				"bc",
				"ca",
				"cb",
				"cc",
				"aaa",
				"aab",
				"aac",
				"aba",
				"abb",
				"abc",
				"aca",
				"acb",
				"acc",
				"baa",
				"bab",
				"bac",
				"bba",
				"bbb",
				"bbc",
				"bca",
				"bcb",
				"bcc",
				"caa",
				"cab",
				"cac",
				"cba",
				"cbb",
				"cbc",
				"cca",
				"ccb",
				"ccc"};

			// Action
			Utilities::DictionaryGenerator generator(3, "abc", "dict.txt");
			generator.GenerateDictionary();

			// Préparation assert

			// On va chercher tous les mots dans le fichier généré
			string line;
			ifstream ifile("dict.txt");

			vector<string> ACTUAL_DICTIONARY_FILE_WORDS;

			while (getline(ifile, line))
			{
				ACTUAL_DICTIONARY_FILE_WORDS.push_back(line);
			}

			Assert::IsTrue(EXPECTED_DICTIONARY_FILE_WORDS == ACTUAL_DICTIONARY_FILE_WORDS);

		}
	};
}