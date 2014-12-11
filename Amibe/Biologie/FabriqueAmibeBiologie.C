//
// Classe d'FabriqueAmibeBiologie
//

#include "FabriqueAmibeBiologie.h"
#include "AmibeDegatsIrradiationX.h"
#include "AmibeDegatsIrradiationHadron.h"
#include "AmibeMutationIrradiation.h"
#include "AmibeMutationIrradiation2.h"
#include "AmibeProliferation.h"
#include "AmibeDecomposition.h"
#include "AmibeProbaSurvieX.h" 
#include "AmibeProbaSurvieHadron.h"
#include "AmibeTauxProliferation.h"
#include "AmibeProbaMutation.h"
#include "AmibeProbaMutation2.h"
#include <iostream>

using namespace std;

//________________________________________________________
FabriqueAmibeBiologie::FabriqueAmibeBiologie(void):FabriqueStrategie()
{
//
// Constructeur par defaut
//
fNom="FabriqueAmibeBiologie";
fCommentaire="FabriqueAmibeBiologie de base";
mapOfStrategies.clear();
mapOfStrategies["AmibeDegatsIrradiationX"]=new AmibeDegatsIrradiationX();
mapOfStrategies["AmibeDegatsIrradiationHadron"]=new AmibeDegatsIrradiationHadron();
mapOfStrategies["AmibeMutationIrradiation"]=new AmibeMutationIrradiation();
mapOfStrategies["AmibeMutationIrradiation2"]=new AmibeMutationIrradiation2();
mapOfStrategies["AmibeProliferation"]=new AmibeProliferation();
mapOfStrategies["AmibeDecomposition"]=new AmibeDecomposition();
// Modeles avec probabilites
mapOfStrategies["AmibeProbaSurvieX"]=new AmibeProbaSurvieX();
mapOfStrategies["AmibeProbaSurvieHadron"]=new AmibeProbaSurvieHadron();
mapOfStrategies["AmibeTauxProliferation"]=new AmibeTauxProliferation();
mapOfStrategies["AmibeProbaMutation"]=new AmibeProbaMutation();
mapOfStrategies["AmibeProbaMutation2"]=new AmibeProbaMutation2();
}

//________________________________________________________
FabriqueAmibeBiologie::~FabriqueAmibeBiologie(void)
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
Strategie *FabriqueAmibeBiologie::fabriqueStrategie(string nomStrategie)
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
