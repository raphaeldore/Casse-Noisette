#include "stdafx.h"
#include "CrackFactoryParams.h"

using namespace CrackEngine;

CrackFactoryParams::CrackFactoryParams()
{
}


CrackFactoryParams::~CrackFactoryParams()
{
}

void CrackFactoryParams::addParameter(const Parameter & _parameter)
{
	parameters.insert(_parameter);
}

void CrackFactoryParams::setParameters(const set<Parameter>& _parameters)
{
	parameters = _parameters;
}

const string & CrackFactoryParams::getParameterValue(const PARAM_TYPE & _paramType) const
{
	for (auto param : parameters)
	{
		if (param.paramType == _paramType) return param.value;
	}

	throw runtime_error("Parameter does not exist in the set.");
}