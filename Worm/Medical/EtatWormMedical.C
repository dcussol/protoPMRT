//
// Classe EtatWormMedical
//

#include "EtatWormMedical.h"
#include "FabriqueWormMedical.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatWormMedical::EtatWormMedical(void)
{
//
// Constructeur par defaut
//
fNom="EtatWormMedical";
fCommentaire="EtatWormMedical de base";
fTypeEtat="EtatWormMedical";
fFabStrategie=new FabriqueWormMedical();
fBackgroundColor="magenta";
}

//________________________________________________________
EtatWormMedical::~EtatWormMedical(void)
{
//
// Destructeur
//
}

