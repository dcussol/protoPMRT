//
// Classe d'FabriqueWormTraducteur
//

#include "FabriqueWormTraducteur.h"
#include "CopierSainesOriginales.h"
#include <iostream>

using namespace std;

//________________________________________________________
FabriqueWormTraducteur::FabriqueWormTraducteur(void):FabriqueStrategie()
{
//
// Constructeur par defaut
//
fNom="FabriqueWormTraducteur";
fCommentaire="FabriqueWormTraducteur de base";
mapOfStrategies.clear();
mapOfStrategies["CopierSainesOriginales"]=new CopierSainesOriginales();
}

//________________________________________________________
FabriqueWormTraducteur::~FabriqueWormTraducteur(void)
{
//
// Destructeur
//
delete mapOfStrategies["WormDegatsIrradiationX"];
mapOfStrategies.clear();
}

//________________________________________________________
Strategie *FabriqueWormTraducteur::fabriqueStrategie(string nomStrategie)
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
