//
// Classe d'FabriqueAmibeIrradiation
//

#include "FabriqueAmibeIrradiation.h"
#include "AmibeIrradiationX.h"
#include "AmibeIrradiationProton.h"
#include "AmibeIrradiationCarbone.h"
#include <iostream>

using namespace std;

//________________________________________________________
FabriqueAmibeIrradiation::FabriqueAmibeIrradiation(void):FabriqueStrategie()
{
//
// Constructeur par defaut
//
fNom="FabriqueAmibeIrradiation";
fCommentaire="FabriqueAmibeIrradiation de base";
mapOfStrategies.clear();
mapOfStrategies["AmibeIrradiationX"]=new AmibeIrradiationX();
mapOfStrategies["AmibeIrradiationProton"]=new AmibeIrradiationProton();
mapOfStrategies["AmibeIrradiationCarbone"]=new AmibeIrradiationCarbone();
}

//________________________________________________________
FabriqueAmibeIrradiation::~FabriqueAmibeIrradiation(void)
{
//
// Destructeur
//
delete mapOfStrategies["AmibeIrradiationX"];
delete mapOfStrategies["AmibeIrradiationProton"];
delete mapOfStrategies["AmibeIrradiationCarbone"];
mapOfStrategies.clear();
}

//________________________________________________________
Strategie *FabriqueAmibeIrradiation::fabriqueStrategie(string nomStrategie)
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
