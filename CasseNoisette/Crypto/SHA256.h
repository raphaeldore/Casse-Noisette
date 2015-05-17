#pragma once

namespace CustomCrypto
{
	class SHA256 : public IHash
	{
	public:
		~SHA256() override;
		std::string hash(const std::string & _stringToHash) override;
	};
}