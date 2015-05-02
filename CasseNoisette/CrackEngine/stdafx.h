// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclure les en-têtes Windows rarement utilisés

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <set>
#include <iostream>

// TODO: faites référence ici aux en-têtes supplémentaires nécessaires au programme

#include "Parameter.h"
#include "CrackFactoryParams.h"
#include "CrackFactory.h"
#include "ICrackEngine.h"
#include "BruteForce.h"