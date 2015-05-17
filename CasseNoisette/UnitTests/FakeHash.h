#pragma once

namespace CustomCrypto
{
	class FakeHash : public IHash
	{
	public:
		~FakeHash() override;
		std::string hash(const std::string & _stringToHash) override;
	};
}
