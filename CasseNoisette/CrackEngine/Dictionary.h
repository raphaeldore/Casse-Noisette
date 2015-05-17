#pragma once

#include "ICrackEngine.h"

namespace CrackEngine
{
	class Dictionary : public ICrackEngine
	{
	public:
		Dictionary(std::unique_ptr<std::queue<std::string>> _dictionary);
		~Dictionary();

		void Crack() override;
		void setDictionary(std::unique_ptr<std::queue<std::string>> _dictionary);
	private:
		std::unique_ptr<std::queue<std::string>> dictionary;
	};
}

