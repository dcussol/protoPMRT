//
// Classe RouteurBoucleData
//

#include "RouteurBoucleData.h"
#include "Etat.h"
#include "Automate.h"
#include "Jeton.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

//________________________________________________________
RouteurBoucleData::RouteurBoucleData(void):RouteurBoucle()
{
//
// Constructeur par defaut
//
fNom="RouteurBoucleData";
fCommentaire="Routeur Boucle sur une donnee";
fTypeRouteur="RouteurBoucleData";
fNomData="unknown";
}

//________________________________________________________
RouteurBoucleData::~RouteurBoucleData(void)
{
//
// Destructeur
//
}

//________________________________________________________
Etat *RouteurBoucleData::suivant(void)
{
//
// Aiguille suivant l'etat du compteur
//
Etat *suiv=fEtatBoucle;
Jeton *j=fEtat->getJeton();
if(j->getData(fNomData,fCount))
 {
if(fCount >= fCountInit)
  {
  suiv=fEtatSortie;
  }
 }
else
 {
 cout << "La donnee \"" << fNomData 
 << "\" n'existe pas ou n'a pas le bon type." << endl;
 abort();
 }
return suiv;
}

//________________________________________________________
void RouteurBoucleData::lireFichierConfiguration(istream &fin,Automate *a)
{
//
// Configurer le routeur depuis le fichier de configuration
//
RouteurBoucle::lireFichierConfiguration(fin,a);
string line="";
getline(fin,line);
if(line.find("Data=")==0)
 {
 line.replace(0,5,"");
 this->setNomData(line);
 }
}

//________________________________________________________
void RouteurBoucleData::ecrireFichierConfiguration(ostream &fout)
{
//
// Ecrire du routeur dans un fichier de configuration
//
RouteurBoucle::ecrireFichierConfiguration(fout);
fout << "Data=" << fNomData << endl;
}

//________________________________________________________
void RouteurBoucleData::ecrireDotFile(ostream &fout)
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
 fout << " [label=\"" << this->getNomData() <<" < "<< this->getCompteurInitial() << "\",fontcolor=red];" << endl;
 fout << "edge [color=black];" << endl;
 }
if(this->getEtatSortie())
 {
 fout << "edge [color=blue];" << endl;
 fout << e->getNom() << " -> " << this->getEtatSortie()->getNom();
 fout << " [label=\"" << this->getNomData() <<" >= "<< this->getCompteurInitial() << "\",fontcolor=blue];" << endl;
 fout << "edge [color=black];" << endl;
 }
}
