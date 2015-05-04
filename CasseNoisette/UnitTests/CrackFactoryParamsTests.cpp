#include "stdafx.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace CrackEngine;

namespace UnitTests
{
	TEST_CLASS(CrackFactoryParams)
	{
	public:
		unique_ptr<CrackEngine::CrackFactoryParams> crackFactoryParams;
		TEST_METHOD_INITIALIZE(CrackEngineParams_Initialize)
		{
			crackFactoryParams = make_unique<CrackEngine::CrackFactoryParams>();
		}

		TEST_METHOD(getParameterValue_gets_the_parameter_value_with_the_requested_PARAM_TYPE)
		{
			// Arrange
			string EXPECTED_PARAM_VALUE = "/home/rdore/passwords.txt";
			crackFactoryParams->addParameter(Parameter(PARAM_TYPE::PWD_FILE_PATH, "/home/rdore/passwords.txt"));

			// Action
			string ACTUAL_PARAM_VALUE = crackFactoryParams->getParameterValue(PARAM_TYPE::PWD_FILE_PATH);

			// Assert
			Assert::AreEqual(EXPECTED_PARAM_VALUE, ACTUAL_PARAM_VALUE);
		}

		TEST_METHOD(subscript_operator_should_return_parameter_value)
		{
			// Arrange
			string EXPECTED_PARAM_VALUE = "/home/rdore/cracking_results.txt";
			crackFactoryParams->addParameter(Parameter(PARAM_TYPE::RESULTS_FILE_PATH, "/home/rdore/cracking_results.txt"));

			// Action
			string ACTUAL_PARAM_VALUE = crackFactoryParams->operator[](PARAM_TYPE::RESULTS_FILE_PATH);

			// Assert
			Assert::AreEqual(EXPECTED_PARAM_VALUE, ACTUAL_PARAM_VALUE);
		}

		TEST_METHOD(addParameters_adds_all__the_parameters)
		{
			// Arrange
			string EXPECTED_PWD_FILE_PATH = "/home/rdore/passwords.txt";
			string EXPECTED_RESULTS_FILE_PATH = "/home/rdore/cracking_results.txt";
			string EXPECTED_CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_+=";

			set<Parameter> parameters;
			parameters.insert(Parameter(PARAM_TYPE::PWD_FILE_PATH, "/home/rdore/passwords.txt"));
			parameters.insert(Parameter(PARAM_TYPE::RESULTS_FILE_PATH, "/home/rdore/cracking_results.txt"));
			parameters.insert(Parameter(PARAM_TYPE::CHARSET, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_+="));
			crackFactoryParams->setParameters(parameters);

			// Action
			string ACTUAL_PWD_FILE_PATH = crackFactoryParams->operator[](PWD_FILE_PATH);
			string ACTUAL_RESULTS_FILE_PATH = crackFactoryParams->operator[](RESULTS_FILE_PATH);
			string ACTUAL_CHARSET = crackFactoryParams->operator[](CHARSET);

			// Assert
			Assert::AreEqual(EXPECTED_PWD_FILE_PATH, ACTUAL_PWD_FILE_PATH);
			Assert::AreEqual(EXPECTED_RESULTS_FILE_PATH, ACTUAL_RESULTS_FILE_PATH);
			Assert::AreEqual(EXPECTED_CHARSET, ACTUAL_CHARSET);
		}

		TEST_METHOD(getParameterByValue_throws_exception_if_parameter_does_not_exist_in_set)
		{
			// Action (Ici on utilise une expression lambda)

			//// GetParameterByValueFunction est une fonction lambda qui va être appelée par le Assert.
			//// Le Assert vérifie ensuite qu'une exception a été levée.
			auto GetParameterByValueFunction = [this] {crackFactoryParams->getParameterValue(PARAM_TYPE::PWD_FILE_PATH); };

			// Assert
			Assert::ExpectException<runtime_error>(GetParameterByValueFunction);
		}
	};
}