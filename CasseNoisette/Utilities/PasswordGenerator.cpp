#include "stdafx.h"
#include "PasswordGenerator.h"

#include <random>

using namespace std;

string PasswordGenerator::GeneratePassword(const string & _charset, const unsigned int & _lenght)
{
	string generatedPwd;

	for (unsigned int i = 0; i < _lenght; i++)
	{
		generatedPwd += GenerateRandomCharacter(_charset);
	}

	return generatedPwd;
}

char PasswordGenerator::GenerateRandomCharacter(const string& _charset)
{
	// Génère un nombre aléatoire non-déterministe et cryptographiquement sécuritaire
	random_device rd;
	// .. qu'on utilise ensuite comme seed pour le générateur de nombres aléatoires
	mt19937 mt(rd());

	// Produit une plage de valeurs où chaque nombres produit a une probabilité égale d'être produit
	uniform_int_distribution<unsigned int> uniform_distance(0, _charset.length() - 1);

	return _charset.at(uniform_distance(mt));
}