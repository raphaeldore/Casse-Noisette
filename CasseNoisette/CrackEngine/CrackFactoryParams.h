#pragma once
#include "stdafx.h"
#include "Parameter.h"

using namespace std;

namespace CrackEngine
{
	class Parameter;

	class CrackFactoryParams
	{
		friend class CrackFactory;

	public:
		CrackFactoryParams();
		~CrackFactoryParams();

		void addParameter(const Parameter & _parameter);
		void setParameters(const set<Parameter> & _parameters);
		string getParameterValue(const PARAM_TYPE & _paramType) const;

		// Pour acc�der aux �l�ments plus facilement
		string operator[] (const PARAM_TYPE & _paramType) const;

	private:
		set<Parameter> parameters;
	};
}