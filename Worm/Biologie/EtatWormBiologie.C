//
// Classe EtatWormBiologie
//

#include "EtatWormBiologie.h"
#include "FabriqueWormBiologie.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatWormBiologie::EtatWormBiologie(void)
{
//
// Constructeur par defaut
//
fNom="EtatWormBiologie";
fCommentaire="EtatWormBiologie de base";
fTypeEtat="EtatWormBiologie";
fFabStrategie=new FabriqueWormBiologie();
fBackgroundColor="green";
}

//________________________________________________________
EtatWormBiologie::~EtatWormBiologie(void)
{
//
// Destructeur
//
}

