// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//

#pragma once

#include "targetver.h"

#include <map>
#include <memory>
#include <vector>
#include <set>
#include <tuple>
#include <queue>

// En-t�tes pour CppUnitTest
#include "CppUnitTest.h"

// TODO: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme

// Crypto
#include "../Crypto/HashFactory.h"
#include "../Crypto/IHash.h"
#include "../Crypto/MD5.h"
#include "../Crypto/SHA1.h"
#include "../Crypto/SHA256.h"
#include "FakeHash.h"

// CrackEngine
#include "../CrackEngine/Parameter.h"
#include "../CrackEngine/CrackFactoryParams.h"
#include "../CrackEngine/CrackFactory.h"
#include "../CrackEngine/BruteForce.h"
#include "../CrackEngine/CharsetBuilder.h"
#include "../CrackEngine/Dictionary.h"