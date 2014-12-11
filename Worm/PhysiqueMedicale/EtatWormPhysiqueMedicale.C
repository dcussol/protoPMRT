//
// Classe EtatWormPhysiqueMedicale
//

#include "EtatWormPhysiqueMedicale.h"
#include "FabriqueWormPhysiqueMedicale.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatWormPhysiqueMedicale::EtatWormPhysiqueMedicale(void)
{
//
// Constructeur par defaut
//
fNom="EtatWormPhysiqueMedicale";
fCommentaire="EtatWormPhysiqueMedicale de base";
fTypeEtat="EtatWormPhysiqueMedicale";
fFabStrategie=new FabriqueWormPhysiqueMedicale();
fBackgroundColor="lightblue";
}

//________________________________________________________
EtatWormPhysiqueMedicale::~EtatWormPhysiqueMedicale(void)
{
//
// Destructeur
//
}

