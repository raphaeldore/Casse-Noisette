#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
//using namespace CustomCrypto;

namespace UnitTests
{
	TEST_CLASS(SHA512Tests)
	{
	public:

		/*

		Même si on utilise OpenSSL, il faut tester pour s'assurer qu'on utilise
		bien les fonctions (La documentation est horrible...donc il faut tester)

		*/

		unique_ptr<CustomCrypto::SHA512> sha512Instance;

		TEST_METHOD_INITIALIZE(MD5Instance_Initilize)
		{
			sha512Instance = make_unique<CustomCrypto::SHA512>();
		}

		// Pour générer les hashs SHA512, j'ai utilisé ce site : 
		// http://www.tools4noobs.com/online_tools/hash/

		TEST_METHOD(hash_returns_the_correct_sha512_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("hello");
			string EXPECTED_SHA512_HASH("9b71d224bd62f3785d96d46ad3ea3d73319bfbc2890caadae2dff72519673ca72323c3d99ba5c11d7c7acc6e14b8c5da0c4663475c2e5c3adef46f73bcdec043");

			// Action
			string ACTUAL_SHA512_HASH = sha512Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_SHA512_HASH, ACTUAL_SHA512_HASH);
		}

		TEST_METHOD(sha512_hash_of_special_characters_should_return_correct_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("jamesBond007!!)(*&%?");
			string EXPECTED_SHA512_HASH("beb342ad32885a6525ca17d882ad9284e55084649d32915e7d6082444b01293a476b37ca4f92214734985c3abf09cd79a39fc0a48743c314fe218a23e19b6129");

			// Action
			string ACTUAL_SHA512_HASH = sha512Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_SHA512_HASH, ACTUAL_SHA512_HASH);
		}

		TEST_METHOD(sha512_hash_should_works_with_weird_characters)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("éëç~");
			string EXPECTED_SHA512_HASH("875c437e5dd0cf76be824ace504640a2214432ef5c956935a6bec78c204ead1a41d7bf9183b8656c85070dd843a17247532a268fbcf44a469b31cbbb40dbb62f");

			// Action
			string ACTUAL_SHA512_HASH = sha512Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_SHA512_HASH, ACTUAL_SHA512_HASH);
		}

	};
}