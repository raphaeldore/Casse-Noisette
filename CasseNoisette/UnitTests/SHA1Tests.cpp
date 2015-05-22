#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
//using namespace CustomCrypto;

namespace UnitTests
{
	TEST_CLASS(SHA1Tests)
	{
	public:

		/*
		
		Même si on utilise OpenSSL, il faut tester pour s'assurer qu'on utilise
		bien les fonctions (La documentation est horrible...donc il faut tester)
		
		*/

		unique_ptr<CustomCrypto::SHA1> sha1Instance;

		TEST_METHOD_INITIALIZE(MD5Instance_Initilize)
		{
			sha1Instance = make_unique<CustomCrypto::SHA1>();
		}

		// Pour générer les hashs SHA1, j'ai utilisé ce site : 
		// http://www.tools4noobs.com/online_tools/hash/

		TEST_METHOD(hash_returns_the_correct_sha1_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("hello");
			string EXPECTED_SHA1_HASH("aaf4c61ddcc5e8a2dabede0f3b482cd9aea9434d");

			// Action
			string ACTUAL_SHA1_HASH = sha1Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_SHA1_HASH, ACTUAL_SHA1_HASH);
		}

		TEST_METHOD(sha1_hash_of_special_characters_should_return_correct_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("jamesBond007!!)(*&%?");
			string EXPECTED_SHA1_HASH("ea6a776a927e56949c65b213b414d52746ba6191");

			// Action
			string ACTUAL_HASH = sha1Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_SHA1_HASH, ACTUAL_HASH);
		}

		TEST_METHOD(sha1_hash_should_works_with_weird_characters)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("éëç~");
			string EXPECTED_SHA1_HASH("9c3cf33acca8a53da115c640baec6d6b46ca42dc");

			// Action
			string ACTUAL_HASH = sha1Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_SHA1_HASH, ACTUAL_HASH);
		}
	
	};
}