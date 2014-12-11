//
// Classe d'FabriqueEtat
//

#include "FabriqueEtat.h"
#include "Etat.h"
#include "EtatAutomate.h"
#include "EtatRouteur.h"

FabriqueEtat* FabriqueEtat::gFabriqueEtat=0;

//________________________________________________________
FabriqueEtat::FabriqueEtat(void)
{
//
// Constructeur par defaut
//
fNom="FabriqueEtat";
fCommentaire="FabriqueEtat de base";
this->ajouteConstructeur("Etat",Etat::construire);
this->ajouteConstructeur("EtatAutomate",EtatAutomate::construire);
this->ajouteConstructeur("EtatRouteur",EtatRouteur::construire);
}

//________________________________________________________
FabriqueEtat::~FabriqueEtat(void)
{
//
// Destructeur
//
}

//________________________________________________________
Etat *FabriqueEtat::fabriqueEtat(string nomEtat)
{
//
// Appelle le contructeur de la classe 
//
Etat *e=0;
map<string,etatConst>::iterator it=fConstructeursEtats.find(nomEtat);
if(it!=fConstructeursEtats.end())
 {
 e=(it->second)();
 }
else
 {
 cout << "Le type de Etat \"" << nomEtat << "\" n'a pas de constructeur dans cette fabrique."
 << endl;
 }
return e;
}

//________________________________________________________
void FabriqueEtat::ajouteConstructeur(string nomEtat,Etat* (*re)(void))
{
//
// Ajoute un contructeur a la fabrique
//
map<string,etatConst>::iterator it=fConstructeursEtats.find(nomEtat);
if(it!=fConstructeursEtats.end() && re != fConstructeursEtats[nomEtat])
 {
 cout << "ATTENTION!!! ---> le constructeur de l'Etat \"" << nomEtat << "\" est modifie..." <<
 endl;
 }
fConstructeursEtats[nomEtat]=re;
}
