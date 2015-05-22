#pragma once

namespace CustomCrypto
{
	class SHA512 : public IHash
	{
	public:
		~SHA512() override;
		std::string hash(const std::string & _stringToHash) override;
	};
}