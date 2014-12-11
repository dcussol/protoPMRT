//
// Classe EtatAmibeMedical
//

#include "EtatAmibeMedical.h"
#include "FabriqueAmibeMedical.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatAmibeMedical::EtatAmibeMedical(void)
{
//
// Constructeur par defaut
//
fNom="EtatAmibeMedical";
fCommentaire="EtatAmibeMedical de base";
fTypeEtat="EtatAmibeMedical";
fFabStrategie=new FabriqueAmibeMedical();
fBackgroundColor="magenta";
}

//________________________________________________________
EtatAmibeMedical::~EtatAmibeMedical(void)
{
//
// Destructeur
//
}

