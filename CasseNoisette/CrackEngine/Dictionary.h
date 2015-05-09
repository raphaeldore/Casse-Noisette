#pragma once
#include "ICrackEngine.h"

namespace CrackEngine
{
	class Dictionary : public ICrackEngine
	{
	public:
		Dictionary();
		~Dictionary();

		void Crack() override;
		void setDictionary(unique_ptr<queue<string>> _dictionary);
	private:
		unique_ptr<queue<string>> dictionary;
	};
}

