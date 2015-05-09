#pragma once
#include "ICrackEngine.h"

namespace CrackEngine
{
	class Dictionary : public ICrackEngine
	{
	public:
		Dictionary(unique_ptr<queue<string>> _dictionary);
		~Dictionary();

		void Crack() override;
		void setDictionary(unique_ptr<queue<string>> _dictionary);
	private:
		unique_ptr<queue<string>> dictionary;
	};
}

