//
// Classe d'FabriqueWormMedical
//

#include "FabriqueWormMedical.h"
#include "WormStatus.h"
#include <iostream>

using namespace std;

//________________________________________________________
FabriqueWormMedical::FabriqueWormMedical(void):FabriqueStrategie()
{
//
// Constructeur par defaut
//
fNom="FabriqueWormMedical";
fCommentaire="FabriqueWormMedical de base";
mapOfStrategies.clear();
mapOfStrategies["WormStatus"]=new WormStatus();
}

//________________________________________________________
FabriqueWormMedical::~FabriqueWormMedical(void)
{
//
// Destructeur
//
delete mapOfStrategies["WormStatus"];
mapOfStrategies.clear();
}

//________________________________________________________
Strategie *FabriqueWormMedical::fabriqueStrategie(string nomStrategie)
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
