#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
//using namespace CustomCrypto;

namespace UnitTests
{
	TEST_CLASS(SHA256Tests)
	{
	public:

		/*
		
		Même si on utilise OpenSSL, il faut tester pour s'assurer qu'on utilise
		bien les fonctions (La documentation est horrible...donc il faut tester)
		
		*/

		unique_ptr<CustomCrypto::SHA256> sha256Instance;

		TEST_METHOD_INITIALIZE(MD5Instance_Initilize)
		{
			sha256Instance = make_unique<CustomCrypto::SHA256>();
		}

		// Pour générer les hashs HA256, j'ai utilisé ce site : 
		// http://www.tools4noobs.com/online_tools/hash/

		TEST_METHOD(hash_returns_the_correct_sha256_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("hello");
			string EXPECTED_SHA56_HASH("2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824");

			// Action
			string ACTUAL_SHA256_HASH = sha256Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_SHA56_HASH, ACTUAL_SHA256_HASH);
		}

		TEST_METHOD(sha256_hash_of_special_characters_should_return_correct_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("jamesBond007!!)(*&%?");
			string EXPECTED_SHA256_HASH("c84ed22b0b3642a2573a201872b1fbed09b1c2bf24368953d350f52f846b9707");

			// Action
			string ACTUAL_SHA256_HASH = sha256Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_SHA256_HASH, ACTUAL_SHA256_HASH);
		}

		TEST_METHOD(sha256_hash_should_works_with_weird_characters)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("éëç~");
			string EXPECTED_SHA256_HASH("14e76cdb1bbc6437a90bcafecfcad15b3ef66aa4747f0032ef628f5066591fe7");

			// Action
			string ACTUAL_SHA256_HASH = sha256Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_SHA256_HASH, ACTUAL_SHA256_HASH);
		}
	
	};
}