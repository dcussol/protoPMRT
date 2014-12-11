//
// Classe RouteurSimple
//

#include "RouteurSimple.h"
#include "Etat.h"
#include "Automate.h"

//________________________________________________________
RouteurSimple::RouteurSimple(void)
{
//
// Constructeur par defaut
//
fNom="RouteurSimple";
fCommentaire="RouteurSimple de base";
fTypeRouteur="RouteurSimple";
fEtatSuivant=0;
}

//________________________________________________________
RouteurSimple::~RouteurSimple(void)
{
//
// Destructeur
//
}

//________________________________________________________
void RouteurSimple::lireFichierConfiguration(istream &fin,Automate *a)
{
//
// Configurer le routeur depuis le fichier de configuration
//
Routeur::lireFichierConfiguration(fin,a);
string line="";
getline(fin,line);
if(line.find("suivant=")==0)
 {
 line.replace(0,8,"");
 Etat *suivant=a->getEtat(line);
 this->setEtatSuivant(suivant);
 }
}

//________________________________________________________
void RouteurSimple::ecrireFichierConfiguration(ostream &fout)
{
//
// Ecrire l'etat dans un fichier de configuration
//
Routeur::ecrireFichierConfiguration(fout);
if(fEtatSuivant)
 {
 fout << "suivant=" << fEtatSuivant->getNom()<< endl;
 }
else
 {
 fout << "suivant=---> Non Defini!<---" << endl;
 }
}

//________________________________________________________
void RouteurSimple::ecrireDotFile(ostream &fout)
{
//
// ecriture du fichier de configuration de l'automate
//
Etat *e=this->getEtat();
Routeur *rout=this;
if(this->getEtatSuivant())
 {
 fout << e->getNom() << " -> " << this->getEtatSuivant()->getNom() << ";" << endl;
 }
}
