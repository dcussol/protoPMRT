//
// Classe d'FabriqueAmibeTraducteur
//

#include "FabriqueAmibeTraducteur.h"
#include "CopierSainesOriginales.h"
#include <iostream>

using namespace std;

//________________________________________________________
FabriqueAmibeTraducteur::FabriqueAmibeTraducteur(void):FabriqueStrategie()
{
//
// Constructeur par defaut
//
fNom="FabriqueAmibeTraducteur";
fCommentaire="FabriqueAmibeTraducteur de base";
mapOfStrategies.clear();
mapOfStrategies["CopierSainesOriginales"]=new CopierSainesOriginales();
}

//________________________________________________________
FabriqueAmibeTraducteur::~FabriqueAmibeTraducteur(void)
{
//
// Destructeur
//
delete mapOfStrategies["AmibeDegatsIrradiationX"];
mapOfStrategies.clear();
}

//________________________________________________________
Strategie *FabriqueAmibeTraducteur::fabriqueStrategie(string nomStrategie)
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
