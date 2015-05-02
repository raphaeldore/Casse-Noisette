// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclure les en-t�tes Windows rarement utilis�s

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include <iostream>

// TODO: faites r�f�rence ici aux en-t�tes suppl�mentaires n�cessaires au programme

#include "Parameter.h"
#include "CrackFactoryParams.h"
#include "CrackFactory.h"
#include "ICrackEngine.h"
#include "BruteForce.h"