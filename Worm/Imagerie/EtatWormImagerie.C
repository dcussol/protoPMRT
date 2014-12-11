//
// Classe EtatWormImagerie
//

#include "EtatWormImagerie.h"
#include "FabriqueWormImagerie.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatWormImagerie::EtatWormImagerie(void)
{
//
// Constructeur par defaut
//
fNom="EtatWormImagerie";
fCommentaire="EtatWormImagerie de base";
fTypeEtat="EtatWormImagerie";
fFabStrategie=new FabriqueWormImagerie();
fBackgroundColor="pink";
}

//________________________________________________________
EtatWormImagerie::~EtatWormImagerie(void)
{
//
// Destructeur
//
}

