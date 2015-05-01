#pragma once
#include "stdafx.h"


namespace CrackEngine
{
	class ICrackEngine;

	class CrackFactory
	{
	public:
		static CrackFactory * GetCrackFactory();
		std::unique_ptr<ICrackEngine> CreateCrackEngine();
	private:
	};
}