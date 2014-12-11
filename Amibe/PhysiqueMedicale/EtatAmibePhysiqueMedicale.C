//
// Classe EtatAmibePhysiqueMedicale
//

#include "EtatAmibePhysiqueMedicale.h"
#include "FabriqueAmibePhysiqueMedicale.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatAmibePhysiqueMedicale::EtatAmibePhysiqueMedicale(void)
{
//
// Constructeur par defaut
//
fNom="EtatAmibePhysiqueMedicale";
fCommentaire="EtatAmibePhysiqueMedicale de base";
fTypeEtat="EtatAmibePhysiqueMedicale";
fFabStrategie=new FabriqueAmibePhysiqueMedicale();
fBackgroundColor="lightblue";
}

//________________________________________________________
EtatAmibePhysiqueMedicale::~EtatAmibePhysiqueMedicale(void)
{
//
// Destructeur
//
}

