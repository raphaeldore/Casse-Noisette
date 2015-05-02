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
		const string & getParameterValue(const PARAM_TYPE & _paramType) const;

		// Pour accéder aux éléments plus facilement
		const string & operator[] (const PARAM_TYPE & _paramType) const;

	private:
		set<Parameter> parameters;
	};
}