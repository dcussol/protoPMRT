//
// Classe d'FabriqueAmibePhysiqueMedicale
//

#include "FabriqueAmibePhysiqueMedicale.h"
#include "AmibeHDV.h"
#include "AmibeHDEB.h"
#include <iostream>

using namespace std;

//________________________________________________________
FabriqueAmibePhysiqueMedicale::FabriqueAmibePhysiqueMedicale(void):FabriqueStrategie()
{
//
// Constructeur par defaut
//
fNom="FabriqueAmibePhysiqueMedicale";
fCommentaire="FabriqueAmibePhysiqueMedicale de base";
mapOfStrategies.clear();
mapOfStrategies["AmibeHDV"]=new AmibeHDV();
mapOfStrategies["AmibeHDEB"]=new AmibeHDEB();
}

//________________________________________________________
FabriqueAmibePhysiqueMedicale::~FabriqueAmibePhysiqueMedicale(void)
{
//
// Destructeur
//
map<string,Strategie *>::iterator it;
for(it=mapOfStrategies.begin();it!=mapOfStrategies.end();it++)
 {
 delete it->second;
 }
mapOfStrategies.clear();
}

//________________________________________________________
Strategie *FabriqueAmibePhysiqueMedicale::fabriqueStrategie(string nomStrategie)
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
