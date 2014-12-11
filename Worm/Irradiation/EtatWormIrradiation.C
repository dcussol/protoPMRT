//
// Classe EtatWormIrradiation
//

#include "EtatWormIrradiation.h"
#include "FabriqueWormIrradiation.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatWormIrradiation::EtatWormIrradiation(void)
{
//
// Constructeur par defaut
//
fNom="EtatWormIrradiation";
fCommentaire="EtatWormIrradiation de base";
fTypeEtat="EtatWormIrradiation";
fFabStrategie=new FabriqueWormIrradiation();
fBackgroundColor="red";
}

//________________________________________________________
EtatWormIrradiation::~EtatWormIrradiation(void)
{
//
// Destructeur
//
}

