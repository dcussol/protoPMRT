//
// Classe d'FabriqueWormPhysiqueMedicale
//

#include "FabriqueWormPhysiqueMedicale.h"
#include "WormHDV.h"
#include <iostream>

using namespace std;

//________________________________________________________
FabriqueWormPhysiqueMedicale::FabriqueWormPhysiqueMedicale(void):FabriqueStrategie()
{
//
// Constructeur par defaut
//
fNom="FabriqueWormPhysiqueMedicale";
fCommentaire="FabriqueWormPhysiqueMedicale de base";
mapOfStrategies.clear();
mapOfStrategies["WormHDV"]=new WormHDV();
}

//________________________________________________________
FabriqueWormPhysiqueMedicale::~FabriqueWormPhysiqueMedicale(void)
{
//
// Destructeur
//
delete mapOfStrategies["WormHDV"];
mapOfStrategies.clear();
}

//________________________________________________________
Strategie *FabriqueWormPhysiqueMedicale::fabriqueStrategie(string nomStrategie)
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
