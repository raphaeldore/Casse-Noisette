#include "stdafx.h"
#include "BruteForce.h"

using namespace CrackEngine;

BruteForce::BruteForce(const int & _maxPwdLenght) : maxPwdLenght(_maxPwdLenght)
{
	// Groupe de caractères par défaut
	crackingCharset = Charsets::loweralpha;
}

BruteForce::BruteForce(const string& _crackingCharset, const int & _maxPwdLenght) : crackingCharset(_crackingCharset), maxPwdLenght(_maxPwdLenght)
{
}

BruteForce::~BruteForce()
{
}

void BruteForce::Crack()
{
}

void BruteForce::setMaxPwdLenght(const int& _maxPwdLenght)
{
	if (maxPwdLenght < 1) throw runtime_error("_maxPwdLenght devrait être plus grand que 1");

	maxPwdLenght = _maxPwdLenght;
}

void BruteForce::setCrackingCharset(const string& _crackingCharset)
{
	if (_crackingCharset.empty())
	{
		// Charset par défaut
		crackingCharset = Charsets::loweralpha;
		return;
	}

	crackingCharset = _crackingCharset;
}