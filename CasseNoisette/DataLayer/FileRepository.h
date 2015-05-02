#pragma once
#include "stdafx.h"

/*

TODO:
    - Validation du contenu du fichier
    - Utilisation d'un séparateur (ex: username:hashedPassword)
    - Validation du formatage de chaque lignes du fichier
    - Bref, de la robustesse.
*/

using namespace std;

namespace DataLayer
{
    class FileRepository
    {
    public:
        void loadPasswordFile(const string _pwdFilePath);
        vector<string> getAllHashedPasswords() const;
    private:
        vector<string> hashedPasswords;
        bool fileIsEmpty(ifstream & _file) const;
    };

}