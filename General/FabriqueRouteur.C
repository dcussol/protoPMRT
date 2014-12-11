//
// Classe d'FabriqueRouteur
//

#include "FabriqueRouteur.h"
#include "RouteurSimple.h"
#include "RouteurBoucle.h"
#include "RouteurBoucleData.h"

FabriqueRouteur* FabriqueRouteur::gFabriqueRouteur=0;

//________________________________________________________
FabriqueRouteur::FabriqueRouteur(void)
{
//
// Constructeur par defaut
//
fNom="FabriqueRouteur";
fCommentaire="FabriqueRouteur de base";
this->ajouteConstructeur("RouteurSimple",RouteurSimple::construire);
this->ajouteConstructeur("RouteurBoucle",RouteurBoucle::construire);
this->ajouteConstructeur("RouteurBoucleData",RouteurBoucleData::construire);
}

//________________________________________________________
FabriqueRouteur::~FabriqueRouteur(void)
{
//
// Destructeur
//
}

//________________________________________________________
Routeur *FabriqueRouteur::fabriqueRouteur(string nomRouteur)
{
//
// Appelle le contructeur de la classe 
//
Routeur *r=0;
map<string,routConst>::iterator it=fConstructeursRouteurs.find(nomRouteur);
if(it!=fConstructeursRouteurs.end())
 {
 r=(it->second)();
 }
else
 {
 cout << "Le type de routeur \"" << nomRouteur << "\" n'a pas de constructeur dans cette fabrique."
 << endl;
 }
return r;
}

//________________________________________________________
void FabriqueRouteur::ajouteConstructeur(string nomRouteur,Routeur* (*rc)(void))
{
//
// Ajoute un contructeur a la fabrique
//
map<string,routConst>::iterator it=fConstructeursRouteurs.find(nomRouteur);
if(it!=fConstructeursRouteurs.end() && rc != fConstructeursRouteurs[nomRouteur])
 {
 cout << "ATTENTION!!! ---> le constructeur du routeur \"" << nomRouteur << "\" est modifie..." <<
 endl;
 }
fConstructeursRouteurs[nomRouteur]=rc;
}
