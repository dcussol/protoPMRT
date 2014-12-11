//
// Classe Automate
//

#include "Automate.h"
#include "EtatAutomate.h"
#include "UtilitairesString.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

//________________________________________________________
Automate::Automate(void)
{
//
// Constructeur par defaut
//
fNom="Automate";
fCommentaire="Automate de base";
fJeton=0;
fEtatCourant=0;
fFabriqueEtat=FabriqueEtat::get();
fFabriqueRouteur=FabriqueRouteur::get();
fVecteurEtats.clear();
fEnsembleVisiteurs.clear();
}

//________________________________________________________
Automate::~Automate(void)
{
//
// Destructeur
//
fVecteurEtats.clear();
}

//________________________________________________________
void Automate::process(void)
{
//
// Lancement de l'automate
//
// Initialisation des visiteurs
this->initialiseVisiteurs();
// Boucle principale d'execution
this->boucleTraitement();
// Finalisation des visiteurs
this->finaliseVisiteurs();
}

//________________________________________________________
bool Automate::testeProcess(void)
{
//
// Lancement du test de l'automate
//
bool ok=true;
if(fEtatInitial)
 {
 this->setEtatCourant(fEtatInitial);
 fEtatInitial->setJeton(fJeton);
 }
else
 {
 cout << "L'etat initial de l'automate \"" << this->getNom() 
 << "\" n'est pas defini." << endl;
 }
while(fEtatCourant && ok)
 {
 fJeton=fEtatCourant->testeTraitement(ok);
 cout << "Test de l'etat " << fEtatCourant->getNom() <<
 " : ";
 if(ok)
  {
  cout << "Conforme";
  }
 else
  {
  cout << "Non conforme";
  }
 cout << endl;
 if(ok)
  {
  fEtatCourant->setTeste(true);
  vector<Etat *> suivants=fEtatCourant->getSuivants();
  vector<Etat *>::iterator its;
  for(its=suivants.begin();its!=suivants.end() && ok;its++)
   {
   fEtatCourant=*its;
   if(fEtatCourant && !fEtatCourant->estTeste())
    {
    fEtatCourant->setJeton(fJeton);
    ok=this->testeProcess();
    }
   }
  fEtatCourant=0;
  }
 }
if(!ok)
 {
 cout << "Un element de l'automate " << this->getNom() << " n'est pas conforme "
 << endl;
 }
return ok;
}

//________________________________________________________
void Automate::prepareTest(void)
{
//
// Preparation du test de l'automate
//
map<string,Etat *>::iterator it;
cout << "Initialisation des etats pour le test de l'automate "<< this->getNom() << endl;
for(it=fVecteurEtats.begin();it!=fVecteurEtats.end();it++)
 {
 it->second->setTeste(false);
 }
}

//________________________________________________________
void Automate::ecrireFichierConfiguration(ostream &fout)
{
//
// ecriture du fichier de configuration de l'automate
//
vector<Routeur *> vecRouteurs;
fout << "//\n// definition des Etats\n//" << endl;
map<string,Etat *>::iterator it;
for(it=fVecteurEtats.begin();it!=fVecteurEtats.end();it++)
 {
 Etat *e=it->second;
 e->ecrireFichierConfiguration(fout);
 if(e->getRouteur())
  {
  vecRouteurs.push_back(e->getRouteur());
  }
 }

fout << "//\n// definition des Routeurs\n//" << endl;
vector<Routeur *>::iterator itr;
for(itr=vecRouteurs.begin();itr!=vecRouteurs.end();itr++)
 {
 (*itr)->ecrireFichierConfiguration(fout);
 }

map<string,double> params=this->getValeursParametres();
map<string,double>::iterator itp;
fout << "//\n// definition des parametres\n//" << endl;
for(itp=params.begin();itp!=params.end();itp++)
 {
 fout << "parametre " << itp->first << "=" << itp->second << endl;
 }

fout << "//\n// Etat initial de l'automate\n//" << endl;
if(fEtatInitial)
 {
 fout << "EtatInitial " << fEtatInitial->getNom() << endl;
 }
else
 {
 fout << "EtatInitial --->Non Defini!<---"<< endl;
 }
}

//________________________________________________________
void Automate::lireFichierConfiguration(istream &fin)
{
//
// Configuration de l'automate a partir d'un fichier d'entree
//
string line;
while(!fin.eof())
 {
 getline(fin,line);
 if(!fin.eof())
  {
  if(line.find("#")==0 || line.find("//")==0)
   {
   cout << line << endl;
   }
  else
   {
   if(line.find("etat ")==0)
    {
    line.replace(0,5,"");
    Etat *e=fFabriqueEtat->fabriqueEtat(line);
    if(!e)
     {
     cout << "Le nom du type de l'etat est inconnu." << endl;
     abort();
     }
    else
     {
     e->lireFichierConfiguration(fin,this);
     }
    }
   else if(line.find("routeur ")==0)
    {
    line.replace(0,8,"");
    Routeur *r=fFabriqueRouteur->fabriqueRouteur(line);
    if(!r)
     {
     cout << "Le nom du type du routeur est inconnu." << endl;
     abort();
     }
    else
     {
     r->lireFichierConfiguration(fin,this);
     }
    }
   else if(line.find("parametre ")==0)
    {
    line.replace(0,10,"");
    vector<string> splitted=splitString(line,"=");
    this->setValeurParametre(splitted[0],atof(splitted[1].data()));
    }
   else if(line.find("EtatInitial ")==0)
    {
    line.replace(0,12,"");
    this->setEtatInitial(this->getEtat(line));
    }
   else
    {
    cout << "La ligne \"" << line << "\" ne peut pas etre interpretee" << endl;
    abort();
    }
   }
  }
 }
}


//________________________________________________________
void Automate::ecrireDotFile(ostream &fout)
{
//
// ecriture du fichier de configuration de l'automate
//
fout << "digraph " << getNom() << " {" << endl;
//fout << "size=\"20,20\"" << endl;
fout << "ratio=1.5" << endl;
fout << "subgraph cluster" << getNom() << "{" << endl;
map<string,Etat *>::iterator it;
if(fEtatInitial)
 {
 fEtatInitial->ecrireDotFile(fout);
 Routeur *rout=fEtatInitial->getRouteur();
 if(rout)
  {
  rout->ecrireDotFile(fout);
  }
 }
 
for(it=fVecteurEtats.begin();it!=fVecteurEtats.end();it++)
 {
 Etat *e=it->second;
 if(e!=fEtatInitial)
  {
  e->ecrireDotFile(fout);
  Routeur *rout=e->getRouteur();
  if(rout)
   {
   rout->ecrireDotFile(fout);
   }
  }
 }

fout << "label=\"" << getNom() << "\";" << endl;
fout << "}" << endl;
fout << "}" << endl;
}

//________________________________________________________
map<string,double> Automate::getValeursParametres(void)
{
//
// Retourne la liste des valeurs des parametres
//
map<string,double> lstParams;
map<string,Etat *>::iterator it;
for(it=fVecteurEtats.begin();it!=fVecteurEtats.end();it++)
 {
 Etat *e=it->second;
 map<string,double> lstParamsEtat=e->getValeursParametres();
 map<string,double>::iterator itp;
 string prefix=e->getNom();
 prefix+="::";
 for(itp=lstParamsEtat.begin();itp!=lstParamsEtat.end();itp++)
  {
  string nomParam=itp->first;
  nomParam.insert(0,prefix);
  lstParams[nomParam]=itp->second;
  }
 }
return lstParams;
} 

//________________________________________________________
void Automate::setValeursParametres(map<string,double> lstParams)
{
//
// Ajuste les valeurs des parametres de l'automate a partir de la liste
//
map<string,double>::iterator it;
for(it=lstParams.begin();it!=lstParams.end();it++)
 {
 this->setValeurParametre(it->first,it->second);
 }
} 

//________________________________________________________
void Automate::setValeurParametre(string nomParam, double val)
{
//
// Ajuste la valeur d'un parametre
//
vector<string> splitted=splitString(nomParam,"::");
string nomEtat=splitted[0];
Etat *e=this->getEtat(nomEtat);
if(e)
 {
 nomParam.replace(0,nomEtat.length()+2,"");
 e->setValeurParametre(nomParam,val);
 }
else
 {
 cout << "Dans Automate::setValeurParametre(\"" << nomParam <<"\"," << val << ")" << endl;  
 cout << "   -> L'etat \"" << nomEtat << "\" n'est pas connu de l'automate \"" 
 << this->getNom() << "\". Operation annulee." << endl; 
 }
}

//________________________________________________________
void Automate::initialiseVisiteurs(void)
{
//
// initialisation des visiteurs
//
// --> Recherche des visiteurs dans un premier temps
map<string,Etat *>::iterator it;
for(it=fVecteurEtats.begin();it!=fVecteurEtats.end();it++)
 {
 Visiteur *v=it->second->getVisiteur();
 if(v)
  {
  fEnsembleVisiteurs.insert(v);
  }
 }
// --> Initialisation
//cout << "Initialisation des visiteurs de l'automate "<< this->getNom() << endl;
set<Visiteur *>::iterator itv;
for(itv=fEnsembleVisiteurs.begin();itv!=fEnsembleVisiteurs.end();itv++)
 {
 (*itv)->initialisation();
 }
}

//________________________________________________________
void Automate::finaliseVisiteurs(void)
{
//
// finalisation des visiteurs
//
//cout << "Finalisation des visiteurs de l'automate "<< this->getNom() << endl;
set<Visiteur *>::iterator itv;
for(itv=fEnsembleVisiteurs.begin();itv!=fEnsembleVisiteurs.end();itv++)
 {
 (*itv)->finalisation();
 }
}

//________________________________________________________
void Automate::boucleTraitement(void)
{
//
// Boucle principale de traitement
//
if(fEtatInitial)
 {
 this->setEtatCourant(fEtatInitial);
 fEtatInitial->setJeton(fJeton);
 }
else
 {
 cout << "L'etat initial de l'automate \"" << this->getNom() 
 << "\" n'est pas defini." << endl;
 abort();
 }
while(fEtatCourant)
 {
 fJeton=fEtatCourant->traitement();
 fEtatCourant=fEtatCourant->suivant();
 if(fEtatCourant)
  {
  fEtatCourant->setJeton(fJeton);
  }
 }
}

//________________________________________________________
void Automate::printListeEtats(ostream &fout)
{
//
// Preparation du test de l'automate
//
map<string,Etat *>::iterator it;
cout << "Liste des etats de l'automate "<< this->getNom() << endl;
for(it=fVecteurEtats.begin();it!=fVecteurEtats.end();it++)
 {
 Etat *e=it->second;
 fout << it->first << " : " << e;
 if(e)
  {
  fout << " " << e->getNom() << "(" << e->getTypeEtat() << ")"; 
  }
 fout << endl;
 EtatAutomate *ea=dynamic_cast<EtatAutomate *>(e);
 if(ea)
  {
  fout << "---------------------------------" << endl;
  ea->getAutomate()->printListeEtats(fout);
  fout << "---------------------------------" << endl;
  }
 }
}
