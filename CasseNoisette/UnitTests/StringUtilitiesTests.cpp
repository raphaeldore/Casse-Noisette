#include "stdafx.h"
#include "../Utilities/StringUtilities.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{

	TEST_CLASS(StringUtilitiesTests)
	{
	public:
		TEST_METHOD(tolower_should_convert_uppercase_to_lowercase)
		{
			// Arrange
			string uppercaseString = "ABC";
			string expectedResult = "abc";

			// Action
			string actualResult = Utilities::StringUtilities::basicToLower(uppercaseString);

			// Assert
			Assert::AreEqual(expectedResult, actualResult);
		}

	};
}