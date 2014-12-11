//
// Classe d'FabriqueWormBiologie
//

#include "FabriqueWormBiologie.h"
#include "WormDegatsIrradiationX.h"
#include "WormDegatsIrradiationHadron.h"
#include "WormMutationIrradiation.h"
#include "WormMutationIrradiation2.h"
#include "WormProliferation.h"
#include "WormPropagationTumeur.h"
#include "WormCicatrisation.h"
#include "WormDecomposition.h"
#include <iostream>

using namespace std;

//________________________________________________________
FabriqueWormBiologie::FabriqueWormBiologie(void):FabriqueStrategie()
{
//
// Constructeur par defaut
//
fNom="FabriqueWormBiologie";
fCommentaire="FabriqueWormBiologie de base";
mapOfStrategies.clear();
mapOfStrategies["WormDegatsIrradiationX"]=new WormDegatsIrradiationX();
mapOfStrategies["WormDegatsIrradiationHadron"]=new WormDegatsIrradiationHadron();
mapOfStrategies["WormMutationIrradiation"]=new WormMutationIrradiation();
mapOfStrategies["WormMutationIrradiation2"]=new WormMutationIrradiation2();
mapOfStrategies["WormProliferation"]=new WormProliferation();
mapOfStrategies["WormPropagationTumeur"]=new WormPropagationTumeur();
mapOfStrategies["WormCicatrisation"]=new WormCicatrisation();
mapOfStrategies["WormDecomposition"]=new WormDecomposition();
}

//________________________________________________________
FabriqueWormBiologie::~FabriqueWormBiologie(void)
{
//
// Destructeur
//
delete mapOfStrategies["WormDegatsIrradiationX"];
delete mapOfStrategies["WormDegatsIrradiationHadron"];
delete mapOfStrategies["WormMutationIrradiation"];
delete mapOfStrategies["WormProliferation"];
delete mapOfStrategies["WormPropagationTumeur"];
delete mapOfStrategies["WormCicatrisation"];
delete mapOfStrategies["WormDecomposition"];
mapOfStrategies.clear();
}

//________________________________________________________
Strategie *FabriqueWormBiologie::fabriqueStrategie(string nomStrategie)
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
