#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace CrackEngine;

namespace UnitTests
{
	TEST_CLASS(CharsetBuilder)
	{
	public:
		shared_ptr<CrackEngine::CharsetBuilder> charsetBuilder;
		TEST_METHOD_INITIALIZE(BruteForce_Initialize)
		{
			charsetBuilder = make_shared<CrackEngine::CharsetBuilder>();
		}

		TEST_METHOD(can_build_lower_alpha_charset)
		{
			// Arrange
			const string EXPECTED_CHARSET = "abcdefghijklmnopqrstuvwxyz";

			// Action
			charsetBuilder->enableLowerAlpha();
			const string ACTUAL_CHARSET = charsetBuilder->BuildCharset();
			
			// Assert
			Assert::AreEqual(EXPECTED_CHARSET, ACTUAL_CHARSET);
		}

		TEST_METHOD(can_create_upperalpha_charset)
		{
			// Arrange
			const string EXPECTED_CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

			// Action
			charsetBuilder->enableUpperAlpha();
			const string ACTUAL_CHARSET = charsetBuilder->BuildCharset();

			// Assert
			Assert::AreEqual(EXPECTED_CHARSET, ACTUAL_CHARSET);
		}

		TEST_METHOD(can_create_numeric_charset)
		{
			// Arrange
			const string EXPECTED_CHARSET = "0123456789";

			// Action
			charsetBuilder->enableNumeric();
			const string ACTUAL_CHARSET = charsetBuilder->BuildCharset();

			// Assert
			Assert::AreEqual(EXPECTED_CHARSET, ACTUAL_CHARSET);
		}

		TEST_METHOD(can_create_space_charset)
		{
			// Arrange
			const string EXPECTED_CHARSET = " ";

			// Action
			charsetBuilder->enableSpace();
			const string ACTUAL_CHARSET = charsetBuilder->BuildCharset();

			// Assert
			Assert::AreEqual(EXPECTED_CHARSET, ACTUAL_CHARSET);
		}

		TEST_METHOD(can_create_special_caracters_charset)
		{
			// Arrange
			const string EXPECTED_CHARSET = "!@#$%^&*()-_+=";

			// Action
			charsetBuilder->enableSpecial();
			const string ACTUAL_CHARSET = charsetBuilder->BuildCharset();

			// Assert
			Assert::AreEqual(EXPECTED_CHARSET, ACTUAL_CHARSET);
		}

		TEST_METHOD(can_use_custom_charset)
		{
			// Arrange
			const string CUSTOM_CHARSET(";[~");
			const string EXPECTED_CHARSET = CUSTOM_CHARSET;

			// Action
			charsetBuilder->addCustomCharset(CUSTOM_CHARSET);
			const string ACTUAL_CHARSET = charsetBuilder->BuildCharset();

			// Assert
			Assert::AreEqual(EXPECTED_CHARSET, ACTUAL_CHARSET);
		}

		TEST_METHOD(if_duplicate_caracter_is_addded_to_custom_charset_then_it_is_removed)
		{
			// Arrange
			const string CUSTOM_CHARSET("ovrbfibcufnitxlpoxxc");
			const string EXPECTED_CHARSET = "abcdefghijklmnopqrstuvwxyz";

			// Action
			charsetBuilder->enableLowerAlpha();
			charsetBuilder->addCustomCharset(CUSTOM_CHARSET);
			const string ACTUAL_CHARSET = charsetBuilder->BuildCharset();

			// Assert
			Assert::AreEqual(EXPECTED_CHARSET, ACTUAL_CHARSET);
		}

		TEST_METHOD(can_mix_multiple_charsets)
		{
			// Arrange
			const string EXPECTED_CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_+=";

			// Action
			charsetBuilder->enableUpperAlpha();
			charsetBuilder->enableSpecial();
			const string ACTUAL_CHARSET = charsetBuilder->BuildCharset();

			// Assert
			Assert::AreEqual(EXPECTED_CHARSET, ACTUAL_CHARSET);
		}

		TEST_METHOD(can_use_constructor_instead_of_methods_to_choose_what_to_include_in_charset)
		{
			// Arrange
			const string EXPECTED_CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

			// Action
			CrackEngine::CharsetBuilder charsetBuilder_2{
				true,
				true,
				true,
				false,
				false
			};

			const string ACTUAL_CHARSET = charsetBuilder_2.BuildCharset();

			// Assert
			Assert::AreEqual(EXPECTED_CHARSET, ACTUAL_CHARSET);
		}

	};
}
