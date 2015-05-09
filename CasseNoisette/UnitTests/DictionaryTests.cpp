#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace CrackEngine;

namespace UnitTests
{
	TEST_CLASS(Dictionary)
	{
	public:
		unique_ptr<CrackEngine::Dictionary> dictionaryEngine;
		unique_ptr<queue<string>> CrackingDictionary;
		TEST_METHOD_INITIALIZE(Dictionary_Initialise)
		{
			CrackingDictionary = make_unique<queue<string>>();
			CrackingDictionary->push("sausage");
			CrackingDictionary->push("blubber");
			CrackingDictionary->push("pencil");
			CrackingDictionary->push("cloud");
			CrackingDictionary->push("moon");
			CrackingDictionary->push("water");
			CrackingDictionary->push("computer");
			CrackingDictionary->push("school");
			CrackingDictionary->push("network");
			CrackingDictionary->push("hammer");
			CrackingDictionary->push("epic007!;;!");
			dictionaryEngine = make_unique<CrackEngine::Dictionary>(move(CrackingDictionary));
			dictionaryEngine->setPwdHashFunction("MD5");
		}

		TEST_METHOD(crack_can_crack_one_password_hash_with_dictionary)
		{
			// Arrange
			multimap<string, string> hashedPasswords;
			hashedPasswords.insert(make_pair("8b433670258f79578f9a4e5ea388b007", "randomUser007"));
			dictionaryEngine->setHashedPasswords(hashedPasswords);

			vector<tuple<string, string, string>> EXPECTED_RESULTS{
				make_tuple("randomUser007", "8b433670258f79578f9a4e5ea388b007", "sausage")
			};

			// Action
			dictionaryEngine->Crack();
			auto ACTUAL_RESULTS = dictionaryEngine->getResults();


			// Assert
			Assert::IsTrue(EXPECTED_RESULTS == ACTUAL_RESULTS);
		}

		TEST_METHOD(can_crack_multiple_passwords_with_dictionary)
		{
			// Arrange
			multimap<string, string> hashedPasswords;
			hashedPasswords.insert(make_pair("8b433670258f79578f9a4e5ea388b007", "randomUser007"));
			hashedPasswords.insert(make_pair("08da50bd109c7fb1bec49d15ae86e55f", "randomUser008"));
			hashedPasswords.insert(make_pair("a8f6830bce790a8a67fc2e84e12093ba", "randomUser009"));
			hashedPasswords.insert(make_pair("b7790fd9b94faa21b180935b582a1e19", "randomUser010"));

			dictionaryEngine->setHashedPasswords(hashedPasswords);

			vector<tuple<string, string, string>> EXPECTED_RESULTS{
				make_tuple("randomUser007", "8b433670258f79578f9a4e5ea388b007", "sausage"),
				make_tuple("randomUser008", "08da50bd109c7fb1bec49d15ae86e55f", "blubber"),
				make_tuple("randomUser009", "a8f6830bce790a8a67fc2e84e12093ba", "pencil"),
				make_tuple("randomUser010", "b7790fd9b94faa21b180935b582a1e19", "epic007!;;!")
			};

			// Action
			dictionaryEngine->Crack();
			auto ACTUAL_RESULTS = dictionaryEngine->getResults();


			// Assert
			Assert::IsTrue(EXPECTED_RESULTS == ACTUAL_RESULTS);
		}

		TEST_METHOD(if_multiple_users_have_the_same_password_then_getResults_returns_the_same_password_for_all_of_them)
		{
			// Arrange
			multimap<string, string> hashedPasswords;
			hashedPasswords.insert(make_pair("8b433670258f79578f9a4e5ea388b007", "randomUser007"));
			hashedPasswords.insert(make_pair("8b433670258f79578f9a4e5ea388b007", "randomUser008"));
			hashedPasswords.insert(make_pair("a8f6830bce790a8a67fc2e84e12093ba", "randomUser009"));
			hashedPasswords.insert(make_pair("8b433670258f79578f9a4e5ea388b007", "randomUser010"));

			dictionaryEngine->setHashedPasswords(hashedPasswords);

			vector<tuple<string, string, string>> EXPECTED_RESULTS{
				make_tuple("randomUser007", "8b433670258f79578f9a4e5ea388b007", "sausage"),
				make_tuple("randomUser008", "8b433670258f79578f9a4e5ea388b007", "sausage"),
				make_tuple("randomUser010", "8b433670258f79578f9a4e5ea388b007", "sausage"),
				make_tuple("randomUser009", "a8f6830bce790a8a67fc2e84e12093ba", "pencil")
			};

			// Action
			dictionaryEngine->Crack();
			auto ACTUAL_RESULTS = dictionaryEngine->getResults();


			// Assert
			Assert::IsTrue(EXPECTED_RESULTS == ACTUAL_RESULTS);
		}

		TEST_METHOD(if_password_is_not_in_dictionary_then_no_password_is_found)
		{
			// Arrange
			multimap<string, string> hashedPasswords;
			hashedPasswords.insert(make_pair("e1568c571e684e0fb1724da85d215dc0", "randomUser007"));
			dictionaryEngine->setHashedPasswords(hashedPasswords);

			vector<tuple<string, string, string>> EXPECTED_RESULTS;

			// Action
			dictionaryEngine->Crack();
			auto ACTUAL_RESULTS = dictionaryEngine->getResults();


			// Assert
			Assert::IsTrue(EXPECTED_RESULTS == ACTUAL_RESULTS);
		}

		TEST_METHOD(setDictionary_throws_invalid_argument_if_dictionary_is_empty)
		{
			// Action
			auto setDictionaryInvalidArgumentFunction = [this]{dictionaryEngine->setDictionary(make_unique<queue<string>>()); };

			// Assert
			Assert::ExpectException<invalid_argument>(setDictionaryInvalidArgumentFunction);
		}
	};
}