#include "stdafx.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace CustomCrypto;

namespace UnitTests
{
	TEST_CLASS(MD5)
	{
	public:
		unique_ptr<CustomCrypto::MD5> md5Instance;
		TEST_METHOD_INITIALIZE(MD5Instance_Initilize)
		{
			md5Instance = make_unique<CustomCrypto::MD5>();
		}

		/*
		On test avec les exemples données dans le document
		d'implémentation de l'algorithme: https://tools.ietf.org/html/rfc1321
		(à la fin complètement du fichier, "A.5 Test Suite")

		Je retranscopie les tests ici:
		MD5 ("") = d41d8cd98f00b204e9800998ecf8427e
		MD5 ("a") = 0cc175b9c0f1b6a831c399e269772661
		MD5 ("abc") = 900150983cd24fb0d6963f7d28e17f72
		MD5 ("message digest") = f96b697d7cb7938d525a2f31aaf161d0
		MD5 ("abcdefghijklmnopqrstuvwxyz") = c3fcd3d76192e4007dfb496cca67e13b
		MD5 ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") =
		d174ab98d277d9f5a5611c2c9f419d9f
		MD5 ("123456789012345678901234567890123456789012345678901234567890123456
		78901234567890") = 57edf4a22be3c955ac49da2e2107b67a

		*/

		TEST_METHOD(md5_hash_of_empty_string_return_correct_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("");
			string EXPECTED_MD5_HASH("d41d8cd98f00b204e9800998ecf8427e");

			// Action
			string actual_hash = md5Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_MD5_HASH, actual_hash);
		}

		TEST_METHOD(md5_hash_of_single_letter_a_returns_correct_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("a");
			string EXPECTED_MD5_HASH("0cc175b9c0f1b6a831c399e269772661");
			
			// Action
			string actual_hash = md5Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_MD5_HASH, actual_hash);
		}

		TEST_METHOD(md5_hash_of_abc_should_return_correct_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("abc");
			string EXPECTED_MD5_HASH("900150983cd24fb0d6963f7d28e17f72");

			// Action
			string actual_hash = md5Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_MD5_HASH, actual_hash);
		}

		TEST_METHOD(md5_hash_of_message_digest_should_return_correct_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("message digest");
			string EXPECTED_MD5_HASH("f96b697d7cb7938d525a2f31aaf161d0");

			// Action
			string actual_hash = md5Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_MD5_HASH, actual_hash);
		}

		TEST_METHOD(md5_hash_of_abcdefghijklmnopqrstuvwxyz_should_return_correct_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("abcdefghijklmnopqrstuvwxyz");
			string EXPECTED_MD5_HASH("c3fcd3d76192e4007dfb496cca67e13b");

			// Action
			string actual_hash = md5Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_MD5_HASH, actual_hash);
		}

		TEST_METHOD(md5_hash_of_all_alphanumeric_characters_should_return_correct_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
			string EXPECTED_MD5_HASH("d174ab98d277d9f5a5611c2c9f419d9f");

			// Action
			string actual_hash = md5Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_MD5_HASH, actual_hash);
		}

		TEST_METHOD(md5_hash_of_long_list_of_numbers_should_return_correct_hash)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
			string EXPECTED_MD5_HASH("57edf4a22be3c955ac49da2e2107b67a");

			// Action
			string actual_hash = md5Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_MD5_HASH, actual_hash);
		}

		TEST_METHOD(md5_hash_of_special_characters_should_return_correct_hash)
		{
			// Note: Pour me générer un hash md5 j'ai utilisé cet outil en ligne: http://www.md5.net/md5-generator//

			// Arrange
			string PLAINTEXT_TO_HASH("jamesBond007!!)(*&%?");
			string EXPECTED_MD5_HASH("2f5be544d077b3ffb5e32a01ee5f864c");

			// Action
			string actual_hash = md5Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_MD5_HASH, actual_hash);
		}

		TEST_METHOD(md5_hash_of_amazing_programmer_should_return_correct_hash)
		{
			// Note: Pour me générer un hash md5 j'ai utilisé cet outil en ligne: http://www.md5.net/md5-generator//
			// Note 2: Ce test n'est pas une blague. À un moment donné ce test ne passait pas ;)

			// Arrange
			string PLAINTEXT_TO_HASH("Raphaël Doré");
			string EXPECTED_MD5_HASH("f4b57df8decd87efc977c727b7fd355f");

			// Action
			string actual_hash = md5Instance->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_MD5_HASH, actual_hash);
		}

		TEST_METHOD(same_instance_of_md5_computes_correct_hash_of_multiple_strings)
		{
			// Note: Pour me générer un hash md5 j'ai utilisé cet outil en ligne: http://www.md5.net/md5-generator//

			vector<string> wordsToTest {
				"sausage",
				"blubber",
				"pencil",
				"cloud",
				"moon",
				"water",
				"computer",
				"school",
				"network",
				"hammer"
			};
			
			vector<string> md5ExpectedHashs = {
				"8b433670258f79578f9a4e5ea388b007",
				"08da50bd109c7fb1bec49d15ae86e55f",
				"a8f6830bce790a8a67fc2e84e12093ba",
				"a1234b3161b4fbfdfb96dd576b65bbea",
				"6d4db5ff0c117864a02827bad3c361b9",
				"9460370bb0ca1c98a779b1bcc6861c2c",
				"df53ca268240ca76670c8566ee54568a",
				"7516c3b35580b3490248629cff5e498c",
				"91e02cd2b8621d0c05197f645668c5c4",
				"5f9901fc60b769b523d0dd8e79b3fe08"
			};

			for (unsigned int i = 0; i < 10; i++)
			{
				Assert::AreEqual(md5Instance->hash(wordsToTest[i]), md5ExpectedHashs[i]);
			}
		}
	};
}