#pragma once

#include <set>
#include "Parameter.h"

namespace CrackEngine
{
	class CrackFactoryParams
	{
	public:
		CrackFactoryParams();
		~CrackFactoryParams();

		void addParameter(const Parameter & _parameter);
		void setParameters(const std::set<Parameter> & _parameters);
		std::string getParameterValue(const PARAM_TYPE & _paramType) const;

		// Pour accéder aux éléments plus facilement
		std::string operator[] (const PARAM_TYPE & _paramType) const;

	private:
		std::set<Parameter> parameters;
	};
}