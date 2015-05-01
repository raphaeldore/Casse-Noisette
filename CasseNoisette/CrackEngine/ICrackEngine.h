#pragma once
#include "stdafx.h"

namespace CrackEngine
{
	class ICrackEngine
	{
	public:
		virtual ~ICrackEngine() {}
		virtual void Crack() = 0;
	private:
	};
}