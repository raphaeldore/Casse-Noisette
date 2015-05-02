#include "stdafx.h"
#include "Parameter.h"

using namespace CrackEngine;

Parameter::Parameter(const PARAM_TYPE& _paramType, const string& _value) : paramType(_paramType), value(_value)
{

}

Parameter::~Parameter()
{
}

bool Parameter::operator<(const Parameter& rhs) const
{
	return paramType < rhs.paramType;
}