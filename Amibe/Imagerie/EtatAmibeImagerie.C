//
// Classe EtatAmibeImagerie
//

#include "EtatAmibeImagerie.h"
#include "FabriqueAmibeImagerie.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatAmibeImagerie::EtatAmibeImagerie(void)
{
//
// Constructeur par defaut
//
fNom="EtatAmibeImagerie";
fCommentaire="EtatAmibeImagerie de base";
fTypeEtat="EtatAmibeImagerie";
fFabStrategie=new FabriqueAmibeImagerie();
fBackgroundColor="pink";
}

//________________________________________________________
EtatAmibeImagerie::~EtatAmibeImagerie(void)
{
//
// Destructeur
//
}

