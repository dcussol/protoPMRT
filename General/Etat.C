//
// Classe Etat
//

#include "Etat.h"
#include "UtilitairesString.h"
#include "Automate.h"

#include <iostream>

using namespace std;

//________________________________________________________
Etat::Etat(void)
{
//
// Constructeur par defaut
//
fNom="Etat";
fCommentaire="Etat de base";
fTypeEtat="Etat";
fJeton=0;
fFabStrategie=0;
fVisiteur=0;
fRouteur=0;
fStrategie=0;
fNomStrategie="inconnue";
fParametresStrategie.clear();
fBackgroundColor="white";
}

//________________________________________________________
Etat::~Etat(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *Etat::traitement(void)
{
//
// Methode de traitement
//
 Jeton *j=0;
 if(fVisiteur)
  {
  fVisiteur->setEtat(this);
  fVisiteur->preTraitement();
  }
 if(fFabStrategie)
  {
  Strategie *strat=fFabStrategie->fabriqueStrategie(fNomStrategie);
  fStrategie=strat;
  if(strat)
   {
   this->setParametresStrategie(strat);
   j=strat->resoudre(fJeton);
   }
  else
   {
   cout << "La strategie \"" << fNomStrategie << 
   "\" n'existe pas pour la fabrique \"" << fFabStrategie->getNom() << "\"" << endl;
   }
  }
 else
  {
  cout << "Pas de fabrique de strategie pour l'etat \"" 
  << this->getNom() << "\"" << endl;
  }
 if(fVisiteur)
  {
  fVisiteur->postTraitement();
  }
 return j;
}

//________________________________________________________
Jeton *Etat::testeTraitement(bool &ok)
{
//
// Methode de traitement
//
 Jeton *j=0;
 if(fFabStrategie)
  {
  Strategie *strat=fFabStrategie->fabriqueStrategie(fNomStrategie);
  if(strat)
   {
   j=strat->testResoudre(fJeton,ok);
   cout << "Test de la strategie " << strat->getNom() <<
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
   }
  else
   {
   cout << "La strategie \"" << fNomStrategie << 
   "\" n'existe pas pour la fabrique \"" << fFabStrategie->getNom() << "\"" << endl;
   }
  }
 else
  {
  cout << "Pas de fabrique de strategie pour l'etat \"" 
  << this->getNom() << "\"" << endl;
  }
 return j;
}

//________________________________________________________
Etat *Etat::suivant(void)
{
//
// Retourne l'etat suivant
//
Etat *suiv=0;
if(fRouteur)
 {
 suiv=fRouteur->suivant();
 }
return suiv;
}

//________________________________________________________
vector<Etat *> Etat::getSuivants(void)
{
//
// Liste les etats suivants possibles pour cet etat
// cette information est presente dans le routeur
//
vector<Etat *> suivants;
if(fRouteur)
 {
 suivants=fRouteur->getSuivants();
 }
return suivants;
}

//________________________________________________________
double Etat::getValeurParametre(string nomParam)
{
//
// retourne la valeur d'un parametre de la strategie
//
vector<string> splitted=splitString(nomParam,"::");
string nomStrat=splitted[0];
 nomParam.replace(0,nomStrat.length()+2,"");
return (fParametresStrategie[nomStrat])[nomParam];
}

//________________________________________________________
void Etat::setValeurParametre(string nomParam, double val)
{
//
// ajuste la valeur d'un parametre de la strategie
//
vector<string> splitted=splitString(nomParam,"::");
string nomStrat=splitted[0];
if(nomStrat == "Routeur")
 {
  if(fRouteur)
  {
  nomParam.replace(0,nomStrat.length()+2,"");
  fRouteur->setValeurParametre(nomParam,val);
  }
 }
else
 {
 nomParam.replace(0,nomStrat.length()+2,"");
 (fParametresStrategie[nomStrat])[nomParam]=val;
 }
}

//________________________________________________________
void Etat::setParametresStrategie(Strategie *s)
{
//
// Envoie les valeur des parametres a la strategie
//
map<string,double> parStrat=fParametresStrategie[s->getNom()];
map<string,double>::iterator it;
for(it=parStrat.begin();it!=parStrat.end();it++)
 {
 //cout << "Valeur " << getNom() << "::" << s->getNom() << "::" << it->first << " -> " << it->second << endl; 
 s->setValeurParametre(it->first,it->second);
 }
}

//________________________________________________________
void Etat::ecrireFichierConfiguration(ostream &fout)
{
//
// Ecrire l'etat dans un fichier de configuration
//
fout << "etat " << this->getTypeEtat() << endl;
fout << "nom=" << this->getNom() << endl ;
fout << "commentaire=" << this->getCommentaire() << endl;
fout << "strategie=" << this->getNomStrategie() << endl;
// map<string, map<string,double> >::iterator its;
// map<string,double>::iterator it;
// for(its=fParametresStrategie.begin();its!=fParametresStrategie.end();its++)
//  {
//  map<string,double> parStrat=fParametresStrategie[its->first];
//  for(it=parStrat.begin();it!=parStrat.end();it++)
//   {
//   fout << "parametre " << its->first << "::" << it->first << "=" << it->second << endl;
//   }
//  }
if(fVisiteur)
 {
 fout << "visiteur=" << fVisiteur->getNom() << endl;
 }
fout << "--> Fin <--" << endl;
}

//________________________________________________________
void Etat::lireFichierConfiguration(istream &fin,Automate *a)
{
//
// Configurer l'etat depuis un fichier de configuration
//
string line="";
bool ok=true;
while(ok)
 {
 ok=false;
 getline(fin,line);
 if(!fin.eof())
  {
  ok=true;
  if(line=="--> Fin <--")
   {
   ok=false;
   }
  else if(line.find("nom=")==0)
   {
   line.replace(0,4,"");
   this->setNom(line);
   }
  else if(line.find("commentaire=")==0)
   {
   line.replace(0,12,"");
   this->setCommentaire(line);
   }
  else if(line.find("strategie=")==0)
   {
   line.replace(0,10,"");
   this->setNomStrategie(line);
   }
  }
 }
a->ajouteEtat(this);
}

//________________________________________________________
void Etat::ecrireDotFile(ostream &fout)
{
//
// ecriture du fichier de configuration de l'automate
//
Etat *e=this;
// Entete de l'etat
fout << e->getNom() << endl;
fout << "[ " << endl << " shape = none" <<endl;
fout << " label =  <<table border=\"0\" cellspacing=\"0\" > " << endl;
fout << "              <tr><td border=\"1\" bgcolor=\"" 
     << fBackgroundColor <<"\">" << e->getTypeEtat() 
     << "</td><td border=\"1\">" << e->getNom() <<"</td></tr>" << endl;
// strategie de l'etat
fout << "              <tr><td colspan=\"2\" border=\"1\"></td></tr>" << endl;
if(e->getNomStrategie()!="inconnue")
 {
 fout << "              <tr><td colspan=\"2\" border=\"1\"><FONT color=\"blue\">" << e->getNomStrategie() << "</FONT></td></tr>" << endl;
 // Parametres de la strategie
 map<string,double> params=this->getValeursParametres();
 map<string,double>::iterator it;
 for(it=params.begin();it!=params.end();it++)
  {
  string parName=it->first;
  if(parName.find("Routeur")==string::npos)
   {
   vector<string> splitted=splitString(it->first,"::");
   fout << "             <tr><td  border=\"1\"><FONT color=\"magenta\">" << splitted.back() << "</FONT></td>";
   fout << "<td  border=\"1\"><FONT color=\"magenta\">" << it->second << "</FONT></td></tr>";
   fout << endl;
   }
  }
 }
else
 {
 fout << "              <tr><td colspan=\"2\" border=\"1\">Sans stratégie</td></tr>" << endl;
 } 
// Visiteur de l'etat
if(e->getVisiteur())
 {
 fout << "              <tr><td colspan=\"2\" border=\"1\"></td></tr>" << endl;
 fout << "              <tr><td border=\"1\">Visiteur</td>" << endl;
 fout << "              <td border=\"1\"><FONT color=\"magenta\">" <<
 e->getVisiteur()->getNom() << "</FONT></td></tr>" << endl;
 }
else
 {
 //fout << "              <td border=\"1\"></td></tr>" << endl;
 }
fout << "               </table>>" << endl << "]" << endl << endl;

}

//________________________________________________________
map<string,double> Etat::getValeursParametres(void)
{
//
// Retourne la liste des valeurs des parametres
//
map<string,double> lstParams;
map<string,double>::iterator itp;

// Parametres de la strategie
string nomParam="";
string prefix="";
if(fStrategie)
 {
 prefix=fStrategie->getNom();
 prefix+="::";
 map<string,double> lstParamsStrategie=fStrategie->getValeursParametres();
 for(itp=lstParamsStrategie.begin();itp!=lstParamsStrategie.end();itp++)
  {
  nomParam=itp->first;
  nomParam.insert(0,prefix);
  lstParams[nomParam]=itp->second;
  }
 }
// Parametres dans la liste des parametres de l'etat
map<string, map<string,double> >::iterator its;
map<string,double>::iterator it;
for(its=fParametresStrategie.begin();its!=fParametresStrategie.end();its++)
 {
 prefix=its->first;
 prefix+="::";
 map<string,double> parStrat=fParametresStrategie[its->first];
 for(it=parStrat.begin();it!=parStrat.end();it++)
  {
  nomParam=it->first;
  nomParam.insert(0,prefix);
  lstParams[nomParam]=it->second;
  }
 }

// Parametres du routeur
Routeur *r=this->getRouteur();
if(r)
 {
 map<string,double> lstParamsRouteur=r->getValeursParametres();
 prefix="Routeur::";
 for(itp=lstParamsRouteur.begin();itp!=lstParamsRouteur.end();itp++)
  {
  string nomParam=itp->first;
  nomParam.insert(0,prefix);
  lstParams[nomParam]=itp->second;
  }
 }
return lstParams;
} 
