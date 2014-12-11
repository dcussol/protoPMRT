//
// Classe EtatAmibeTraducteur
//

#include "EtatAmibeTraducteur.h"
#include "FabriqueAmibeTraducteur.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatAmibeTraducteur::EtatAmibeTraducteur(void):Etat()
{
//
// Constructeur par defaut
//
fNom="EtatAmibeTraducteur";
fCommentaire="EtatAmibeTraducteur de base";
fTypeEtat="EtatAmibeTraducteur";
fFabStrategie=new FabriqueAmibeTraducteur();
fBackgroundColor="orange";
}

//________________________________________________________
EtatAmibeTraducteur::~EtatAmibeTraducteur(void)
{
//
// Destructeur
//
}

