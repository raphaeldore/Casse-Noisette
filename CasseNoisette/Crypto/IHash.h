#pragma once

namespace CustomCrypto
{
	class IHash
	{
	public :
		virtual ~IHash() {}

		virtual std::string hash(const std::string & _stringToHash) = 0;
	};
}