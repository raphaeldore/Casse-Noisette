#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace CrackEngine;

namespace IntegrationTests
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
			vector<string> hashedPasswords{ "6d4db5ff0c117864a02827bad3c361b9" };
			unsigned int EXPECTED_RESULTS_VECTOR_SIZE = 1;
			string EXPECTED_DECRYPTED_PASSWORD = "moon";
			bruteForce->setHashedPasswords(hashedPasswords);

			// Action
			bruteForce->Crack();
			vector<string> results = bruteForce->getResults();
			string ACTUAL_DECRYPTED_PASSWORD = results.at(0); // Il y a seulement 1 hash dans le fichier simple_password.txt

			// Assert
			Assert::AreEqual(EXPECTED_RESULTS_VECTOR_SIZE, results.size());
			Assert::AreEqual(EXPECTED_DECRYPTED_PASSWORD, ACTUAL_DECRYPTED_PASSWORD);
		}

		TEST_METHOD(crack_can_crack_password_with_numbers)
		{
			// Arrange
			vector<string> hashedPasswords{ "e1568c571e684e0fb1724da85d215dc0" };
			unsigned int EXPECTED_RESULTS_VECTOR_SIZE = 1;
			string EXPECTED_DECRYPTED_PASSWORD = "l33t";
			bruteForce->setCrackingCharset(lowerAlphaNumericCrackingCharset);
			bruteForce->setHashedPasswords(hashedPasswords);

			// Action
			bruteForce->Crack();
			vector<string> results = bruteForce->getResults();
			string ACTUAL_DECRYPTED_PASSWORD = results.at(0); // Il y a seulement 1 hash dans le fichier simple_password.txt

			// Assert
			Assert::AreEqual(EXPECTED_RESULTS_VECTOR_SIZE, results.size());
			Assert::AreEqual(EXPECTED_DECRYPTED_PASSWORD, ACTUAL_DECRYPTED_PASSWORD);
		}

		TEST_METHOD(crack_can_crack_file_containing_multiple_passwords)
		{
			// Arrange
			vector<string> hashedPasswords{ "106a6c241b8797f52e1e77317b96a201", "06d80eb0c50b49a509b49f2424e8c805", "2a1585a864d9e67627c6ae04c807a2c5", "0a16bc32f55683128983f223de242942" };
			unsigned int EXPECTED_RESULTS_VECTOR_SIZE = 4;
			vector<string> EXPECTED_DECRYPTED_PASSWORDS = { "home", "dog", "final", "ink" };
			bruteForce->setHashedPasswords(hashedPasswords);

			// Action
			bruteForce->Crack();
			vector<string> ACTUAL_DECRYPTED_PASSWORDS = bruteForce->getResults();

			// Assert
			Assert::AreEqual(EXPECTED_RESULTS_VECTOR_SIZE, ACTUAL_DECRYPTED_PASSWORDS.size());

			
			for (unsigned int i = 0; i < EXPECTED_RESULTS_VECTOR_SIZE; ++i)
			{
				Assert::AreEqual(EXPECTED_DECRYPTED_PASSWORDS[i], ACTUAL_DECRYPTED_PASSWORDS[i]);
			}
			
		}

		TEST_METHOD(if_maxPwdLenght_too_small_then_results_vector_empty)
		{
			// Arrange
			unsigned int EXPECTED_RESULTS_VECTOR_SIZE = 0;
			bruteForce->setMaxPwdLenght(2);
			vector<string> hashedPasswords{ "6d4db5ff0c117864a02827bad3c361b9" };
			bruteForce->setHashedPasswords(hashedPasswords);

			// Action
			bruteForce->Crack();
			vector<string> results = bruteForce->getResults();

			// Assert
			Assert::AreEqual(EXPECTED_RESULTS_VECTOR_SIZE, results.size());
		}
	};
}