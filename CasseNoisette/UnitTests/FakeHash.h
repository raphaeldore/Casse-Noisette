#pragma once

namespace CustomCrypto
{
	class FakeHash : public IHash
	{
	public:
		~FakeHash() override;
		string hash(const string & _stringToHash) override;
	};
}
