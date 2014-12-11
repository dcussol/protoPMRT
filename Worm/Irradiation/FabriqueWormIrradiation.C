//
// Classe d'FabriqueWormIrradiation
//

#include "FabriqueWormIrradiation.h"
#include "WormIrradiationX.h"
#include "WormIrradiationProton1I.h"
#include "WormIrradiationProton2I.h"
#include "WormIrradiationCarbone.h"
#include <iostream>

using namespace std;

//________________________________________________________
FabriqueWormIrradiation::FabriqueWormIrradiation(void):FabriqueStrategie()
{
//
// Constructeur par defaut
//
fNom="FabriqueWormIrradiation";
fCommentaire="FabriqueWormIrradiation de base";
mapOfStrategies.clear();
mapOfStrategies["WormIrradiationX"]=new WormIrradiationX();
mapOfStrategies["WormIrradiationProton1I"]=new WormIrradiationProton1I();
mapOfStrategies["WormIrradiationProton2I"]=new WormIrradiationProton2I();
mapOfStrategies["WormIrradiationCarbone"]=new WormIrradiationCarbone();
}

//________________________________________________________
FabriqueWormIrradiation::~FabriqueWormIrradiation(void)
{
//
// Destructeur
//
delete mapOfStrategies["WormIrradiationX"];
delete mapOfStrategies["WormIrradiationProton1I"];
delete mapOfStrategies["WormIrradiationProton2I"];
delete mapOfStrategies["WormIrradiationCarbone"];
mapOfStrategies.clear();
}

//________________________________________________________
Strategie *FabriqueWormIrradiation::fabriqueStrategie(string nomStrategie)
{
//
// Instanciation du probleme a partir de la chaine de caracteres
//
Strategie *p=mapOfStrategies[nomStrategie];
if(!p)
 {
 cout << "Erreur : le probleme \"" << nomStrategie << "\" n'existe pas dans cette fabrique."
 << endl;
 }
return p;
}
