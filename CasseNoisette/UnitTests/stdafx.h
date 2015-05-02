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

// En-t�tes pour CppUnitTest
#include "CppUnitTest.h"

// TODO: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme

#include "../Crypto/HashFactory.h"
#include "../Crypto/IHash.h"
#include "../Crypto/MD5.h"
#include "../Crypto/SHA1.h"
#include "../Crypto/SHA256.h"
#include "FakeHash.h"

#include "../CrackEngine/Parameter.h"
#include "../CrackEngine/CrackFactoryParams.h"