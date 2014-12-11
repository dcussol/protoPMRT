//
// Classe Routeur
//

#include "Routeur.h"
#include "Etat.h"
#include "Automate.h"

//________________________________________________________
Routeur::Routeur(void)
{
//
// Constructeur par defaut
//
fNom="Routeur";
fCommentaire="Routeur de base";
fTypeRouteur="Routeur";
fSuivants.clear();
}

//________________________________________________________
Routeur::~Routeur(void)
{
//
// Destructeur
//
}

//________________________________________________________
void Routeur::lireFichierConfiguration(istream &fin,Automate *a)
{
//
// Configurer le routeur depuis le fichier de configuration
//
string line="";
getline(fin,line);
if(line.find("nom=")==0)
  {
  line.replace(0,4,"");
  this->setNom(line);
  }
getline(fin,line);
if(line.find("commentaire=")==0)
  {
  line.replace(0,12,"");
  this->setCommentaire(line);
  }
getline(fin,line);
if(line.find("etat=")==0)
  {
  line.replace(0,5,"");
  Etat *e=a->getEtat(line);
  e->setRouteur(this);
  }
}

//________________________________________________________
void Routeur::ecrireFichierConfiguration(ostream &fout)
{
//
// Ecrire l'etat dans un fichier de configuration
//
fout << "routeur " << this->getTypeRouteur() << endl;
fout << "nom=" << this->getNom() << endl;
fout << "commentaire=" << this->getCommentaire() << endl;
fout << "etat=" << this->getEtat()->getNom() << endl;
}

//________________________________________________________
void Routeur::ecrireDotFile(ostream &fout)
{
//
// ecriture du fichier de configuration de l'automate
//
Etat *e=this->getEtat();
Routeur *rout=this;
if(rout)
 {
 vector<Etat *> vSuiv=rout->getSuivants();
 vector<Etat *>::iterator its;
 for(its=vSuiv.begin();its!=vSuiv.end();its++)
  {
  fout << e->getNom() << " -> " << (*its)->getNom() << ";" << endl;
  }
 }
}
