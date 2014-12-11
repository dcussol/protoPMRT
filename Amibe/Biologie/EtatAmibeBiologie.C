//
// Classe EtatAmibeBiologie
//

#include "EtatAmibeBiologie.h"
#include "FabriqueAmibeBiologie.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatAmibeBiologie::EtatAmibeBiologie(void)
{
//
// Constructeur par defaut
//
fNom="EtatAmibeBiologie";
fCommentaire="EtatAmibeBiologie de base";
fTypeEtat="EtatAmibeBiologie";
fFabStrategie=new FabriqueAmibeBiologie();
fBackgroundColor="green";
}

//________________________________________________________
EtatAmibeBiologie::~EtatAmibeBiologie(void)
{
//
// Destructeur
//
}

