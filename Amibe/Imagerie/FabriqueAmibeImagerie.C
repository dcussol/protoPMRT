//
// Classe d'FabriqueAmibeImagerie
//

#include "FabriqueAmibeImagerie.h"
#include "AmibeImagerie.h"
#include "AmibeImagerie2.h"
#include <iostream>

using namespace std;

//________________________________________________________
FabriqueAmibeImagerie::FabriqueAmibeImagerie(void):FabriqueStrategie()
{
//
// Constructeur par defaut
//
fNom="FabriqueAmibeImagerie";
fCommentaire="FabriqueAmibeImagerie de base";
mapOfStrategies.clear();
mapOfStrategies["AmibeImagerie"]=new AmibeImagerie();
mapOfStrategies["AmibeImagerie2"]=new AmibeImagerie2();
}

//________________________________________________________
FabriqueAmibeImagerie::~FabriqueAmibeImagerie(void)
{
//
// Destructeur
//
delete mapOfStrategies["AmibeImagerie"];
delete mapOfStrategies["AmibeImagerie2"];
mapOfStrategies.clear();
}

//________________________________________________________
Strategie *FabriqueAmibeImagerie::fabriqueStrategie(string nomStrategie)
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
