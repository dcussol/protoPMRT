//
// Classe Strategie
//

#include "Strategie.h"

//________________________________________________________
Strategie::Strategie(void)
{
//
// Constructeur par defaut
//
fNom="Strategie";
fCommentaire="Strategie de base";
}

//________________________________________________________
Strategie::~Strategie(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *Strategie::testResoudre(Jeton *j,bool &ok)
{
//
// test de le conformite de la stategie
//
Jeton *jRetour=0;
ok=this->peutOperer(j);
if(ok)
 {
 jRetour=this->genereDonnee(j);
 }
return jRetour;
}
