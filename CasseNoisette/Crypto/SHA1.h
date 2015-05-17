#pragma once

namespace CustomCrypto
{
	class SHA1 : public IHash
	{
	public:
		~SHA1() override;
		std::string hash(const std::string & _stringToHash) override;
	};
}