//
// Classe EtatWormTraducteur
//

#include "EtatWormTraducteur.h"
#include "FabriqueWormTraducteur.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatWormTraducteur::EtatWormTraducteur(void):Etat()
{
//
// Constructeur par defaut
//
fNom="EtatWormTraducteur";
fCommentaire="EtatWormTraducteur de base";
fTypeEtat="EtatWormTraducteur";
fFabStrategie=new FabriqueWormTraducteur();
fBackgroundColor="orange";
}

//________________________________________________________
EtatWormTraducteur::~EtatWormTraducteur(void)
{
//
// Destructeur
//
}

