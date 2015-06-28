#include "stdafx.h"
#include "../Utilities/GuessHash.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{

	TEST_CLASS(GuessHashTests)
	{
	public:
		TEST_METHOD(guess_should_return_true_if_hash_was_identified)
		{
			// Arrange
			string hash = "a09272b53419ab95507cdf127329336d";
			string identifiedFunction;
			bool EXPECTED_RETURN_VALUE = true;

			// Action
			bool ACTUAL_RETURN_VALUE = Utilities::GuessHash::Guess(hash, identifiedFunction);

			// Assert
			Assert::AreEqual(EXPECTED_RETURN_VALUE, ACTUAL_RETURN_VALUE);
		}

		TEST_METHOD(guess_should_return_false_if_hash_was_not_identified)
		{
			// Arrange
			string hash = "unknown_hash_type";
			string identifiedFunction;
			bool EXPECTED_RETURN_VALUE = false;

			// Action
			bool ACTUAL_RETURN_VALUE = Utilities::GuessHash::Guess(hash, identifiedFunction);

			// Assert
			Assert::AreEqual(EXPECTED_RETURN_VALUE, ACTUAL_RETURN_VALUE);
		}

		TEST_METHOD(guess_should_correctly_identify_valid_md5_hash)
		{
			// Arrange
			string hash = "a09272b53419ab95507cdf127329336d";
			string EXPECTED_HASH_FUNCTION = "MD5";
			string ACTUAL_HASH_FUNCTION;

			// Action
			Utilities::GuessHash::Guess(hash, ACTUAL_HASH_FUNCTION);

			// Assert
			Assert::AreEqual(EXPECTED_HASH_FUNCTION, ACTUAL_HASH_FUNCTION);
		}

		TEST_METHOD(guess_should_correctly_identify_valid_SHA1_hash)
		{
			// Arrange
			string hash = "46dcd4dd65b63d106b8cfb4aad906b23716cc613";
			string EXPECTED_HASH_FUNCTION = "SHA-1";
			string ACTUAL_HASH_FUNCTION;

			// Action
			Utilities::GuessHash::Guess(hash, ACTUAL_HASH_FUNCTION);

			// Assert
			Assert::AreEqual(EXPECTED_HASH_FUNCTION, ACTUAL_HASH_FUNCTION);
		}

		TEST_METHOD(guess_should_correctly_identify_valid_SHA256_hash)
		{
			// Arrange
			string hash = "9e78b43ea00edcac8299e0cc8df7f6f913078171335f733a21d5d911b6999132";
			string EXPECTED_HASH_FUNCTION = "SHA-256";
			string ACTUAL_HASH_FUNCTION;

			// Action
			Utilities::GuessHash::Guess(hash, ACTUAL_HASH_FUNCTION);

			// Assert
			Assert::AreEqual(EXPECTED_HASH_FUNCTION, ACTUAL_HASH_FUNCTION);
		}

		TEST_METHOD(guess_should_correctly_identify_valid_SHA512_hash)
		{
			// Arrange
			string hash = "6ab10af8ba889a65796d58fce59dc5f02ea78744255ccee70e555ff18932a876fa1f02bd81478224af8540e752cc5deb83d5d445c198d04065d6d05be8b4f4e7";
			string EXPECTED_HASH_FUNCTION = "SHA-512";
			string ACTUAL_HASH_FUNCTION;

			// Action
			Utilities::GuessHash::Guess(hash, ACTUAL_HASH_FUNCTION);

			// Assert
			Assert::AreEqual(EXPECTED_HASH_FUNCTION, ACTUAL_HASH_FUNCTION);
		}

		TEST_METHOD(guess_should_correctly_identify_valid_uppercase_hash)
		{
			// Arrange
			string hash = "A09272B53419AB95507CDF127329336D";
			string EXPECTED_HASH_FUNCTION = "MD5";
			string ACTUAL_HASH_FUNCTION;

			// Action
			Utilities::GuessHash::Guess(hash, ACTUAL_HASH_FUNCTION);

			// Assert
			Assert::AreEqual(EXPECTED_HASH_FUNCTION, ACTUAL_HASH_FUNCTION);
		}

	};
}