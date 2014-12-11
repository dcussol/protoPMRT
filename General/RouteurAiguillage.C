//
// Classe RouteurAiguillage
//

#include "RouteurAiguillage.h"
#include "Etat.h"

//________________________________________________________
RouteurAiguillage::RouteurAiguillage(void):Routeur()
{
//
// Constructeur par defaut
//
fNom="RouteurAiguillage";
fCommentaire="RouteurAiguillage de base";
fTypeRouteur="RouteurAiguillage";
fMapSuivants.clear();
}

//________________________________________________________
RouteurAiguillage::~RouteurAiguillage(void)
{
//
// Destructeur
//
}

//________________________________________________________
Etat *RouteurAiguillage::suivant(void)
{
//
// Retourne l'Etat suivant selon que la condition est verifiee
//
Etat *suivant=0;
map<fonc,Etat *>::iterator it;
for(it=fMapSuivants.begin();it!=fMapSuivants.end() && !suivant;it++)
 {
 fonc f=it->first;
 if(f(fEtat))
  {
  suivant=it->second;
  }
 }
return suivant;
}
 
//________________________________________________________
vector<Etat *> RouteurAiguillage::getSuivants(void)
{
//
// Retourne le vecteur des Etats suivants du routeur
//
fSuivants.clear();
map<fonc,Etat *>::iterator it;
for(it=fMapSuivants.begin();it!=fMapSuivants.end();it++)
 {
 fSuivants.push_back(it->second);
 }
return fSuivants;
}
