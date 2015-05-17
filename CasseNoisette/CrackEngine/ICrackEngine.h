#pragma once

namespace CustomCrypto
{
	class IHash;
}

namespace CrackEngine
{
	class ICrackEngine
	{
	public:
		virtual ~ICrackEngine() {}
		virtual void Crack() = 0;
		void cancelCrack();
		void setHashedPasswords(const std::multimap<std::string, std::string> & _hashedPasswords);
		void setPwdHashFunction(const std::string & _pwdHashFunction);
		std::vector<std::tuple<std::string, std::string, std::string>> getResults();
	protected:
		typedef std::vector<std::tuple<std::string, std::string, std::string>> StringTupleVector;

		CustomCrypto::IHash * hashAlgorithm;
		std::multimap<std::string, std::string> hashedPasswords;
		StringTupleVector results;
		volatile bool running = false;
	};
}