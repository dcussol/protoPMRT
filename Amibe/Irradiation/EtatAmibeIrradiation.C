//
// Classe EtatAmibeIrradiation
//

#include "EtatAmibeIrradiation.h"
#include "FabriqueAmibeIrradiation.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatAmibeIrradiation::EtatAmibeIrradiation(void)
{
//
// Constructeur par defaut
//
fNom="EtatAmibeIrradiation";
fCommentaire="EtatAmibeIrradiation de base";
fTypeEtat="EtatAmibeIrradiation";
fFabStrategie=new FabriqueAmibeIrradiation();
fBackgroundColor="red";
}

//________________________________________________________
EtatAmibeIrradiation::~EtatAmibeIrradiation(void)
{
//
// Destructeur
//
}

