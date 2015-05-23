#include "stdafx.h"
#include "BruteForce.h"
#include "CharsetBuilder.h"

using namespace CrackEngine;
using namespace std;

BruteForce::BruteForce(const int & _maxPwdLenght, const string& _crackingCharset)
{
	setMaxPwdLenght(_maxPwdLenght);
	setCrackingCharset(_crackingCharset);
}

BruteForce::~BruteForce()
{
}

void BruteForce::Crack()
{
	running = true;
	for (const auto hashedPassword : ICrackEngine::hashedPasswords)
	{
		string result = Crack(hashedPassword.first);

		if (result != "")
		{
			results.push_back(make_tuple(hashedPassword.second, hashedPassword.first, result));
		}
	}
}

void BruteForce::setMaxPwdLenght(const int& _maxPwdLenght)
{
	if (_maxPwdLenght <= 1) throw invalid_argument("_maxPwdLenght devrait être plus grand que 1");

	maxPwdLenght = _maxPwdLenght;
}

void BruteForce::setCrackingCharset(const string & _crackingCharset)
{
	if (_crackingCharset.empty())
	{
		// Charset par défaut
		crackingCharset = Charsets::loweralpha;
		return;
	}

	crackingCharset = _crackingCharset;
}

string BruteForce::Crack(const string& _hashedPassword) const
{
	/* Largement basé sur cette réponse sur StackOverflow: http://codereview.stackexchange.com/a/44639 */

	// Longeur max du mot de passe: maxPwdLenght + 1
	string password("");
	password.resize(maxPwdLenght + 1);

	// passwordGuess commence par pointer vers le dernier caractère de 'password'. Au fil
	// du cassage on le fera grandir en lui ajoutant des caractères à sa gauche.
	// Ex: password = "       ba", passwordGuess = "ba"
	char* passwordGuess = &password[maxPwdLenght - 1];

	/*
	Explication du processus:
	- Mots de passe de 1 caractère.
	    - On commence avec le premier caractère du charset.
	    - On incrémente jusqu'à-ce qu'on se rends au dernier caractère du charset
	    - Lorqu'on atteint le dernier caractère, on repart du premier caractère du charset
	      et on shift le caractère actuel vers la droite : Ex: "z" -> "a" -> " a"
	- Ensuite, on passe aux mots de passe de 2 caractères.
	    - On ajoute le premier caractère du charset à la position [0] : " a" -> "aa"
	    ...
	    - On reset et on shift vers la droite: "zz" -> "aa" -> " aa"
	- Mot de passe de 3 caractères
	    - On ajoute le premier caractère du charset à la position [0]: " aa" -> "aaa"
	    - ...
	... et ainsi de suite.
	*/

	while (running)
	{
		// Dans cette boucle on essaye toutes les caractères du charset à la position maxPwdLength - 1.
		// Ce n'est jamais le même caractère, puisqu'il est "shifté" vers la droite dans la
		// boucle suivante.
		for (unsigned int i = 0; i < crackingCharset.length(); ++i)
		{
			password[maxPwdLenght - 1] = crackingCharset[i];

			string passwordGuessHash = hashAlgorithm->hash(string(passwordGuess));

			// On compare les hash
			if (passwordGuessHash == _hashedPassword)
			{
				// On a trouvé le mot!!
				return passwordGuess;
			}
		}

		// On incrémente un ou plusieurs caractères vers la gauche, ou bien on décrémente
		// passwordGuess pour le rendre plus gros avant de repasser la boucle ci-haut sur
		// le caractère le plus à droite
		for (int j = maxPwdLenght - 1; j >= 0; --j)
		{
			if (password[j] == 0)
			{
				// Il n'y a pas de caractère à cette position.
				// ...alors on en ajoute un.
				--passwordGuess; // On shift vers la droite (Ex: "aa" -> " aa")

				// On ajoute le prochain caractère du charset à la position
				password[j] = crackingCharset[0]; // " aa" -> "aaa"
				break;
			}

			// On va chercher la position du caractère dans le crackingCharset.
			auto currentCharPosition = crackingCharset.find(password[j]);

			// In incrémente la position du caractère actuel
			++currentCharPosition;
			// On regarde ensuite si le caractère actuel est le dernier caractère du crackingCharset
			if (currentCharPosition < crackingCharset.length())
			{
				// Si le prochain caractère n'est pas le dernier,
				// alors on passe à ce caractère.
				// Ex: "aa" -> on incrémente -> "ba"
				password[j] = crackingCharset[currentCharPosition];
				break;
			}

			// Si c'est le dernier caractère, on retourne au début du crackingCharset.
			password[j] = crackingCharset[0];

			// Si j se rends jusqu'à 0, c'est qu'on a essayé toutes les combinaisons
			// possibles avec le crackingCharset fournis et la longueur max du mot de passe et
			// on a rien trouvé. :(
			if (j == 0)
			{
				return string("");
			}
		}
	}

	// Si on se rends ici, c'est que quelqu'un a appellé la fonction stopCrack() à partir d'un autre thread
	return string("");
}