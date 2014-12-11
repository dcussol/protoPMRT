//
// Classe d'FabriqueAmibeMedical
//

#include "FabriqueAmibeMedical.h"
#include "AmibeStatus.h"
#include "AmibeProbaStatus.h"
#include <iostream>

using namespace std;

//________________________________________________________
FabriqueAmibeMedical::FabriqueAmibeMedical(void):FabriqueStrategie()
{
//
// Constructeur par defaut
//
fNom="FabriqueAmibeMedical";
fCommentaire="FabriqueAmibeMedical de base";
mapOfStrategies.clear();
mapOfStrategies["AmibeStatus"]=new AmibeStatus();
mapOfStrategies["AmibeProbaStatus"]=new AmibeProbaStatus();
}

//________________________________________________________
FabriqueAmibeMedical::~FabriqueAmibeMedical(void)
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
Strategie *FabriqueAmibeMedical::fabriqueStrategie(string nomStrategie)
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
