//
// Classe Jeton
//

#include "Jeton.h"

//________________________________________________________
Jeton::Jeton(void)
{
//
// Constructeur par defaut
//
fNom="Jeton";
fCommentaire="Jeton de base";
fDataServer=new DataServer();
}

//________________________________________________________
Jeton::~Jeton(void)
{
//
// Destructeur
//
delete fDataServer;
}
