#include "stdafx.h"
#include "../Utilities/PasswordGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	static string charset = "abcdefghijklmnopqrstuvwxyz0123456789";

	TEST_CLASS(PasswordGeneratorTests)
	{
	public:
		TEST_METHOD(passwordGenerator_generates_password_of_specified_length)
		{
			// Arrange
			unsigned int EXPECTED_PWD_LENGTH = 15;

			// Action
			string generatedPassword = Utilities::PasswordGenerator::GeneratePassword(charset, EXPECTED_PWD_LENGTH);
			unsigned int ACTUAL_PWD_LENGTH = generatedPassword.length();

			// Assert
			Assert::AreEqual(EXPECTED_PWD_LENGTH, ACTUAL_PWD_LENGTH);
		}

		TEST_METHOD(generatedPassword_contains_only_characters_specified_in_charset)
		{
			// Arrange
			unsigned int PWD_LENGTH = 20;

			// Action
			string generatedPassword = Utilities::PasswordGenerator::GeneratePassword(charset, PWD_LENGTH);

			// Assert (ici je dois improviser dû à la nature de la randomisation)
			for (auto c : generatedPassword)
			{
				if (charset.find(c) == string::npos) Assert::Fail(L"Le mot de passe généré contient au moins un caractère qui n'est pas dans le charset.");
			}

			Assert::IsTrue(true);
		}

		TEST_METHOD(if_charset_contains_only_one_char_then_generatedPassword_contains_only_that_char)
		{
			// Arrange
			unsigned int PWD_LENGTH = 10;
			string oneCharacterCharset = "A";
			string EXPECTED_GENERATED_PWD = "AAAAAAAAAA";

			// Action
			string ACTUAL_GENERATED_PWD = Utilities::PasswordGenerator::GeneratePassword(oneCharacterCharset, PWD_LENGTH);

			// Assert
			Assert::AreEqual(EXPECTED_GENERATED_PWD, ACTUAL_GENERATED_PWD);
		}

	};
}