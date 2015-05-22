#include "stdafx.h"

#pragma warning(push)
#pragma warning(disable: 4800)

//namespace CustomCrypto
//{
//	class MD5;
//	class SHA1;
//	class SHA256;
//}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace CustomCrypto;

namespace UnitTests
{
	TEST_CLASS(HashFactory)
	{
	public:

		CustomCrypto::HashFactory * hashFactory;

		TEST_METHOD_INITIALIZE(HashFactoryTests_Initialize)
		{
			hashFactory = CustomCrypto::HashFactory::GetHashFactory();
		}

		TEST_METHOD(CreateHashAlgorithm_with_MD5_parameter_should_return_an_instance_of_the_md5_class)
		{
			// Action
			IHash * hashAlgorithm = hashFactory->CreateHashAlgorithm("MD5");

			// Assert
			Assert::IsTrue(dynamic_cast<MD5 *>(hashAlgorithm));
		}

		TEST_METHOD(should_be_able_to_compute_md5_hash_with_created_instance)
		{
			// Arrange
			string PLAINTEXT_TO_HASH("message digest");
			string EXPECTED_MD5_HASH("f96b697d7cb7938d525a2f31aaf161d0");

			// Action
			IHash * hashAlgorithm = hashFactory->CreateHashAlgorithm("MD5");
			string actual_hash = hashAlgorithm->hash(PLAINTEXT_TO_HASH);

			// Assert
			Assert::AreEqual(EXPECTED_MD5_HASH, actual_hash);
		}

		TEST_METHOD(CreateHashAlgorithm_with_SHA1_parameter_should_return_an_instance_of_the_SHA1_class)
		{
			// Action
			IHash * hashAlgorithm = hashFactory->CreateHashAlgorithm("SHA-1");

			// Assert
			Assert::IsTrue(dynamic_cast<SHA1 *>(hashAlgorithm));
		}

		TEST_METHOD(CreateHashAlgorithm_with_SHA256_parameter_should_return_an_instance_of_the_SHA256_class)
		{
			// Action
			IHash * hashAlgorithm = hashFactory->CreateHashAlgorithm("SHA-256");

			// Assert
			Assert::IsTrue(dynamic_cast<SHA256 *>(hashAlgorithm));
		}

		TEST_METHOD(CreateHashAlgorithm_with_SHA512_parameter_should_return_an_instance_of_the_SHA512_class)
		{
			// Action
			IHash * hashAlgorithm = hashFactory->CreateHashAlgorithm("SHA-512");

			// Assert
			Assert::IsTrue(dynamic_cast<SHA512 *>(hashAlgorithm));
		}

		TEST_METHOD(CreateHashAlgorithm_with_unknown_parameter_should_throw_exception)
		{
			// Action
			auto CreateHashAlgorithmFunction = [this] { hashFactory->CreateHashAlgorithm("UNKNOWN ALGORITHM"); };

			// Assert
			Assert::ExpectException<invalid_argument>(CreateHashAlgorithmFunction);
		}

		TEST_METHOD(hashfactory_should_be_able_to_create_instance_of_new_hash_algorithm_after_registering_it)
		{
			// Arrange
			unique_ptr<FakeHash> fakeHash = make_unique<FakeHash>();

			// Action
			hashFactory->Register("fakeHash", move(fakeHash));
			IHash * hashAlgorithm = hashFactory->CreateHashAlgorithm("fakeHash");

			// Assert
			Assert::IsTrue(dynamic_cast<FakeHash *>(hashAlgorithm));
		}
	};
}

#pragma warning(pop)