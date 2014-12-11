//
// Classe d'FabriqueWormImagerie
//

#include "FabriqueWormImagerie.h"
#include "WormImagerie.h"
#include <iostream>

using namespace std;

//________________________________________________________
FabriqueWormImagerie::FabriqueWormImagerie(void):FabriqueStrategie()
{
//
// Constructeur par defaut
//
fNom="FabriqueWormImagerie";
fCommentaire="FabriqueWormImagerie de base";
mapOfStrategies.clear();
mapOfStrategies["WormImagerie"]=new WormImagerie();
}

//________________________________________________________
FabriqueWormImagerie::~FabriqueWormImagerie(void)
{
//
// Destructeur
//
delete mapOfStrategies["WormImagerie"];
mapOfStrategies.clear();
}

//________________________________________________________
Strategie *FabriqueWormImagerie::fabriqueStrategie(string nomStrategie)
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
