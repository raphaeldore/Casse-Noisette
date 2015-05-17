#include "stdafx.h"
#include "CrackFactoryParams.h"
#include "Parameter.h"

using namespace CrackEngine;
using namespace std;

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

string CrackFactoryParams::getParameterValue(const PARAM_TYPE & _paramType) const
{
	for (auto param : parameters)
	{
		if (param.paramType == _paramType) return param.value;
	}

	// Lorsque la CrackFactory appelle getParameterValue c'est
	// qu'elle s'attends qu'il y ait un paramètre (paramètre obligatoire). 
	// Si le paramètre n'existe pas, c'est exceptionnel, et on ne peut
	// malheureusement continuer (On ne peut pas, par exemple, créer une
	// instance de DictionaryCrackEngine s'il manque le paramètre DICTIONARY_PATH).
	throw runtime_error("Parameter does not exist in the set.");
}

string CrackFactoryParams::operator[](const PARAM_TYPE& _paramType) const
{
	return getParameterValue(_paramType);
}