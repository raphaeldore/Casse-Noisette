#include "stdafx.h"
#include "Dictionary.h"

using namespace CrackEngine;

Dictionary::Dictionary()
{
}


Dictionary::~Dictionary()
{
}

void Dictionary::Crack()
{
	running = true;
	while (!dictionary->empty() && !hashedPasswords.empty())
	{
		string currentWord = dictionary->front();
		dictionary->pop();
		string currentWordHash = hashAlgorithm->hash(currentWord);

		// Tous les utilisateurs qui ont le même mot de passe
		auto passwordRange = hashedPasswords.equal_range(currentWordHash);

		for (auto it = passwordRange.first; it != passwordRange.second;)
		{
			results.push_back(make_tuple(it->second, it->first, currentWord));

			// On supprime ensuite les passwords ayant ce hash de la liste de passwords.
			it = hashedPasswords.erase(it);
		}

	}
}

void Dictionary::setDictionary(unique_ptr<queue<string>> _dictionary)
{
	if (_dictionary->empty()) throw invalid_argument("Le dictionnaire ne contient aucun mots!");

	dictionary.reset(_dictionary.release());
}