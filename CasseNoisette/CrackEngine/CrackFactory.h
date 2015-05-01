#pragma once
#include "stdafx.h"


namespace CrackEngine
{
	class ICrackEngine;

	class CrackFactory
	{
	public:
		std::unique_ptr<ICrackEngine> CreateCrackEngine();
	private:
	};
}