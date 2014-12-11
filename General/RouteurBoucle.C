//
// Classe RouteurBoucle
//

#include "RouteurBoucle.h"
#include "Etat.h"
#include "Automate.h"

#include <stdlib.h>

//________________________________________________________
RouteurBoucle::RouteurBoucle(void)
{
//
// Constructeur par defaut
//
fNom="RouteurBoucle";
fCommentaire="Routeur Boucle";
fTypeRouteur="RouteurBoucle";
fCountInit=0;
fCount=0;
fEtatBoucle=0;
fEtatSortie=0;
}

//________________________________________________________
RouteurBoucle::~RouteurBoucle(void)
{
//
// Destructeur
//
}

//________________________________________________________
Etat *RouteurBoucle::suivant(void)
{
//
// Aiguille suivant l'etat du compteur
//
Etat *suiv=fEtatBoucle;
fCount--;
if(fCount <= 0)
 {
 suiv=fEtatSortie;
 fCount=fCountInit;
 }
return suiv;
}

//________________________________________________________
void RouteurBoucle::lireFichierConfiguration(istream &fin,Automate *a)
{
//
// Configurer le routeur depuis le fichier de configuration
//
Routeur::lireFichierConfiguration(fin,a);
string line="";
getline(fin,line);
if(line.find("CompteurInitial=")==0)
  {
  line.replace(0,16,"");
  this->setCompteurInitial(atoi(line.data()));
  }
getline(fin,line);
if(line.find("Etat Boucle=")==0)
  {
  line.replace(0,12,"");
  Etat *suivant=a->getEtat(line);
  this->setEtatBoucle(suivant);
  }
getline(fin,line);
if(line.find("Etat Sortie=")==0)
  {
  line.replace(0,12,"");
  if(line!="sans")
   {
   Etat *suivant=a->getEtat(line);
   this->setEtatSortie(suivant);
   }
  }
}

//________________________________________________________
void RouteurBoucle::ecrireFichierConfiguration(ostream &fout)
{
//
// Ecrire du routeur dans un fichier de configuration
//
Routeur::ecrireFichierConfiguration(fout);
fout << "CompteurInitial=" << fCountInit << endl;
fout << "Etat Boucle=" << fEtatBoucle->getNom() << endl;
if(fEtatSortie)
 {
 fout << "Etat Sortie=" << fEtatSortie->getNom() << endl;
 }
else
 {
 fout << "Etat Sortie=sans" << endl;
 }
}

//________________________________________________________
void RouteurBoucle::ecrireDotFile(ostream &fout)
{
//
// ecriture du fichier de configuration de l'automate
//
Etat *e=this->getEtat();
RouteurBoucle *rout=this;
if(this->getEtatBoucle())
 {
 fout << "edge [color=red];" << endl;
 fout << e->getNom() << " -> " << this->getEtatBoucle()->getNom();
 fout << " [label=\"x "<< this->getCompteurInitial() << "\",fontcolor=red];" << endl;
 fout << "edge [color=black];" << endl;
 }
if(this->getEtatSortie())
 {
 fout << "edge [color=blue];" << endl;
 fout << e->getNom() << " -> " << this->getEtatSortie()->getNom() << ";" << endl;
 fout << "edge [color=black];" << endl;
 }
else
 {
 fout << "edge [color=blue];" << endl;
 fout << e->getNom() << " -> sortie;" << endl;
 fout << "edge [color=black];" << endl;
 }
}
