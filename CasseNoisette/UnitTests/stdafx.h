// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés
//

#pragma once

#include "targetver.h"

#include <map>
#include <memory>
#include <vector>
#include <set>

// En-têtes pour CppUnitTest
#include "CppUnitTest.h"

// TODO: faites référence ici aux en-têtes supplémentaires nécessaires au programme

#include "../Crypto/HashFactory.h"
#include "../Crypto/IHash.h"
#include "../Crypto/MD5.h"
#include "../Crypto/SHA1.h"
#include "../Crypto/SHA256.h"
#include "FakeHash.h"

#include "../CrackEngine/Parameter.h"
#include "../CrackEngine/CrackFactoryParams.h"