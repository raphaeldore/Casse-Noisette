#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace CrackEngine;

namespace UnitTests
{
	const static string lowerAlphaNumericCrackingCharset = "abcdefghijklmnopqrstuvwxyz0123456789";

	TEST_CLASS(BruteForce)
	{
	public:
		shared_ptr<CrackEngine::BruteForce> bruteForce;
		TEST_METHOD_INITIALIZE(BruteForce_Initialize)
		{
			// Initialize un bruteForce avec le charset par defaut : abcdefghijklmnopqrstuvwxyz
			bruteForce = make_shared<CrackEngine::BruteForce>(6);
			bruteForce->setPwdHashFunction("MD5");
		}

		TEST_METHOD(initializing_a_bruteForce_with_a_maxPwdLength_smaller_than_2_should_throw_invalid_argument)
		{
			// Arrange
			auto invalidConstructorArgumentFunction = [this] {make_shared<CrackEngine::BruteForce>(1); };

			// Assert
			Assert::ExpectException<invalid_argument>(invalidConstructorArgumentFunction);
		}

		TEST_METHOD(crack_can_crack_simple_password)
		{
			// Arrange
			multimap<string, string> hashedPasswords;
			hashedPasswords.insert(make_pair("6d4db5ff0c117864a02827bad3c361b9", "no_user"));
			unsigned int EXPECTED_RESULTS_VECTOR_SIZE = 1;
			string EXPECTED_DECRYPTED_PASSWORD = "moon";
			bruteForce->setHashedPasswords(hashedPasswords);

			// Action
			bruteForce->Crack();
			vector<tuple<string, string, string>> results = bruteForce->getResults();
			string ACTUAL_DECRYPTED_PASSWORD = get<2>(results.at(0));

			// Assert
			Assert::AreEqual(EXPECTED_RESULTS_VECTOR_SIZE, results.size());
			Assert::AreEqual(EXPECTED_DECRYPTED_PASSWORD, ACTUAL_DECRYPTED_PASSWORD);
		}

		TEST_METHOD(crack_can_crack_password_with_numbers)
		{
			// Arrange
			multimap<string, string> hashedPasswords;
			hashedPasswords.insert(make_pair("e1568c571e684e0fb1724da85d215dc0", "randomUser007"));
			unsigned int EXPECTED_RESULTS_VECTOR_SIZE = 1;

			/// Nom d'utilisateur, Hash, Mot de passe décrypté
			vector<tuple<string, string, string>> EXPECTED_RESULT{ make_tuple("randomUser007", "e1568c571e684e0fb1724da85d215dc0", "l33t") };

			bruteForce->setCrackingCharset(lowerAlphaNumericCrackingCharset);
			bruteForce->setHashedPasswords(hashedPasswords);

			// Action
			bruteForce->Crack();
			vector<tuple<string, string, string>> ACTUAL_RESULT = bruteForce->getResults();

			// Assert
			Assert::AreEqual(EXPECTED_RESULTS_VECTOR_SIZE, ACTUAL_RESULT.size());
			Assert::IsTrue(EXPECTED_RESULT == ACTUAL_RESULT);
		}

		TEST_METHOD(crack_can_crack_multimap_containing_multiple_passwords)
		{
			// Arrange
			multimap<string, string> hashedPasswords;
			hashedPasswords.insert(make_pair("106a6c241b8797f52e1e77317b96a201", "randomUser007"));
			hashedPasswords.insert(make_pair("06d80eb0c50b49a509b49f2424e8c805", "randomUser008"));
			hashedPasswords.insert(make_pair("2a1585a864d9e67627c6ae04c807a2c5", "randomUser009"));
			hashedPasswords.insert(make_pair("0a16bc32f55683128983f223de242942", "randomUser010"));

			unsigned int EXPECTED_RESULTS_VECTOR_SIZE = 4;
			vector<tuple<string, string, string>> EXPECTED_RESULTS{
				make_tuple("randomUser008", "06d80eb0c50b49a509b49f2424e8c805", "dog"),
				make_tuple("randomUser010", "0a16bc32f55683128983f223de242942", "ink"),
				make_tuple("randomUser007", "106a6c241b8797f52e1e77317b96a201", "home"),
				make_tuple("randomUser009", "2a1585a864d9e67627c6ae04c807a2c5", "final")
			};

			bruteForce->setHashedPasswords(hashedPasswords);

			// Action
			bruteForce->Crack();
			vector<tuple<string, string, string>> ACTUAL_RESULTS = bruteForce->getResults();

			// Assert
			Assert::AreEqual(EXPECTED_RESULTS_VECTOR_SIZE, ACTUAL_RESULTS.size());
			Assert::IsTrue(EXPECTED_RESULTS == ACTUAL_RESULTS);
		}

		TEST_METHOD(if_maxPwdLenght_too_small_then_results_vector_empty)
		{
			// Arrange
			unsigned int EXPECTED_RESULTS_VECTOR_SIZE = 0;
			bruteForce->setMaxPwdLenght(2);
			multimap<string, string> hashedPasswords;
			hashedPasswords.insert(make_pair("6d4db5ff0c117864a02827bad3c361b9", "no_user"));
			bruteForce->setHashedPasswords(hashedPasswords);

			// Action
			bruteForce->Crack();
			vector<tuple<string, string, string>> results = bruteForce->getResults();

			// Assert
			Assert::AreEqual(EXPECTED_RESULTS_VECTOR_SIZE, results.size());
		}

		TEST_METHOD(crack_can_crack_simple_sha1_password)
		{
			// Arrange
			multimap<string, string> hashedPasswords;
			hashedPasswords.insert(make_pair("46dcd4dd65b63d106b8cfb4aad906b23716cc613", "no_user"));
			unsigned int EXPECTED_RESULTS_VECTOR_SIZE = 1;
			string EXPECTED_DECRYPTED_PASSWORD = "moon";
			bruteForce->setHashedPasswords(hashedPasswords);
			bruteForce->setPwdHashFunction("SHA-1");

			// Action
			bruteForce->Crack();
			vector<tuple<string, string, string>> results = bruteForce->getResults();
			string ACTUAL_DECRYPTED_PASSWORD = get<2>(results.at(0));

			// Assert
			Assert::AreEqual(EXPECTED_RESULTS_VECTOR_SIZE, results.size());
			Assert::AreEqual(EXPECTED_DECRYPTED_PASSWORD, ACTUAL_DECRYPTED_PASSWORD);
		}

		TEST_METHOD(crack_can_crack_simple_sha256_password)
		{
			// Arrange
			multimap<string, string> hashedPasswords;
			hashedPasswords.insert(make_pair("9e78b43ea00edcac8299e0cc8df7f6f913078171335f733a21d5d911b6999132", "no_user"));
			unsigned int EXPECTED_RESULTS_VECTOR_SIZE = 1;
			string EXPECTED_DECRYPTED_PASSWORD = "moon";
			bruteForce->setHashedPasswords(hashedPasswords);
			bruteForce->setPwdHashFunction("SHA-256");

			// Action
			bruteForce->Crack();
			vector<tuple<string, string, string>> results = bruteForce->getResults();
			string ACTUAL_DECRYPTED_PASSWORD = get<2>(results.at(0));

			// Assert
			Assert::AreEqual(EXPECTED_RESULTS_VECTOR_SIZE, results.size());
			Assert::AreEqual(EXPECTED_DECRYPTED_PASSWORD, ACTUAL_DECRYPTED_PASSWORD);
		}

		TEST_METHOD(crack_can_crack_simple_sha512_password)
		{
			// Arrange
			multimap<string, string> hashedPasswords;
			hashedPasswords.insert(make_pair("6ab10af8ba889a65796d58fce59dc5f02ea78744255ccee70e555ff18932a876fa1f02bd81478224af8540e752cc5deb83d5d445c198d04065d6d05be8b4f4e7", "no_user"));
			unsigned int EXPECTED_RESULTS_VECTOR_SIZE = 1;
			string EXPECTED_DECRYPTED_PASSWORD = "moon";
			bruteForce->setHashedPasswords(hashedPasswords);
			bruteForce->setPwdHashFunction("SHA-512");

			// Action
			bruteForce->Crack();
			vector<tuple<string, string, string>> results = bruteForce->getResults();
			string ACTUAL_DECRYPTED_PASSWORD = get<2>(results.at(0));

			// Assert
			Assert::AreEqual(EXPECTED_RESULTS_VECTOR_SIZE, results.size());
			Assert::AreEqual(EXPECTED_DECRYPTED_PASSWORD, ACTUAL_DECRYPTED_PASSWORD);
		}
	};
}