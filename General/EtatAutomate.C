//
// Classe EtatAutomate
//

#include "EtatAutomate.h"
#include "Automate.h"
#include "UtilitairesString.h"

#include <iostream>
#include <fstream>

using namespace std;

//________________________________________________________
EtatAutomate::EtatAutomate(void):Etat()
{
//
// Constructeur par defaut
//
fNom="EtatAutomate";
fCommentaire="EtatAutomate de base";
fTypeEtat="EtatAutomate";
fAutomate=0;
fBackgroundColor="cyan";
}

//________________________________________________________
EtatAutomate::~EtatAutomate(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *EtatAutomate::traitement(void)
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
 if(fAutomate)
  {
  //fAutomate->setEtatCourant(fEtatInitial);
  fAutomate->setJeton(fJeton);
  fAutomate->boucleTraitement();
  j=fAutomate->getJeton();
  }
 else
  {
  cout << "Pas d'automate pour l'EtatAutomate \"" 
  << this->getNom() << "\"" << endl;
  }
 if(fVisiteur)
  {
  fVisiteur->postTraitement();
  }
 return j;
}

//________________________________________________________
Jeton *EtatAutomate::testeTraitement(bool &ok)
{
//
// Test de l'automate de la classe EtatAutomate
//
 Jeton *j=0;
 ok=false;
 if(fAutomate)
  {
  ok=true;
  //fAutomate->setEtatCourant(fEtatInitial);
  fAutomate->setJeton(fJeton);
  fAutomate->prepareTest();
  ok=fAutomate->testeProcess();
  j=fAutomate->getJeton();
  }
 return j;
}

//________________________________________________________
void EtatAutomate::lireFichierConfiguration(istream &fin,Automate *a)
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
  else if(line.find("automate=")==0)
   {
   line.replace(0,9,"");
   Automate *ae=new Automate();
   cout << "---> Lecture de l'automate " << line << endl;  
   ae->setNom(line);
   line+=".pmrtConf";
   ifstream fin2(line.data());
   ae->lireFichierConfiguration(fin2);
   fin2.close();
   this->setAutomate(ae);
   cout << "---> Lecture effectuee" << endl;
   }
  }
 }
a->ajouteEtat(this);
}

//________________________________________________________
void EtatAutomate::ecrireFichierConfiguration(ostream &fout)
{
//
// Ecrire l'etat dans un fichier de configuration
//
fout << "etat " << this->getTypeEtat() <<endl;
fout << "nom=" << this->getNom() << endl;
fout << "commentaire=" << this->getCommentaire() << endl;
fout << "automate=" << fAutomate->getNom() << endl;
map<string, map<string,double> >::iterator its;
map<string,double>::iterator it;
for(its=fParametresStrategie.begin();its!=fParametresStrategie.end();its++)
 {
 map<string,double> parStrat=fParametresStrategie[its->first];
 for(it=parStrat.begin();it!=parStrat.end();it++)
  {
  fout << "parametre " << its->first << "::" << it->first << "=" << it->second << endl;
  }
 }
if(fVisiteur)
 {
 fout << "visiteur=" << fVisiteur->getNom() << endl;
 }
fout << "--> Fin <--" << endl;

string fName=fAutomate->getNom();
fName+=".pmrtConf";
ofstream fAuto(fName.data());
fAutomate->ecrireFichierConfiguration(fAuto);
fAuto.close();
}

//________________________________________________________
void EtatAutomate::ecrireDotFile(ostream &fout)
{
//
// ecriture du fichier de configuration de l'automate
//
EtatAutomate *e=this;
// Entete de l'etat
fout << e->getNom() << endl;
fout << "[ " << endl << " shape = none" <<endl;
fout << " label =  <<table border=\"0\" cellspacing=\"0\" > " << endl;
fout << "              <tr><td border=\"1\" bgcolor=\"" 
     << fBackgroundColor<< "\">" << e->getTypeEtat() 
     << "</td><td border=\"1\">" << e->getNom() <<"</td></tr>" << endl;
// Automate de l'etat
fout << "              <tr><td colspan=\"2\" border=\"1\"></td></tr>" << endl;
fout << "              <tr><td colspan=\"2\" border=\"1\"><FONT color=\"darkgreen\">" <<
 e->getAutomate()->getNom() << "</FONT></td></tr>" << endl;

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

// Ecriture du fichier .dot de l'automate de l'etat automate
string fName=e->getAutomate()->getNom();
fName+=".dot";
ofstream foutSa(fName.data());
e->getAutomate()->ecrireDotFile(foutSa);
foutSa.close();
}

//________________________________________________________
map<string,double> EtatAutomate::getValeursParametres(void)
{
//
// Retourne la liste des valeurs des parametres
//
map<string,double> lstParams;
map<string,double>::iterator itp;

// Parametres de l'automate
string prefix="Automate::";
map<string,double> lstParamsAutomate=fAutomate->getValeursParametres();
for(itp=lstParamsAutomate.begin();itp!=lstParamsAutomate.end();itp++)
 {
 string nomParam=itp->first;
 nomParam.insert(0,prefix);
 lstParams[nomParam]=itp->second;
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

//________________________________________________________
void EtatAutomate::setValeurParametre(string nomParam, double val)
{
//
// ajuste la valeur d'un parametre de la strategie
//
vector<string> splitted=splitString(nomParam,"::");
string nomStrat=splitted[0];
if(nomStrat == "Automate")
 {
 nomParam.replace(0,nomStrat.length()+2,"");
 fAutomate->setValeurParametre(nomParam,val);
 }
else if(nomStrat == "Routeur" && fRouteur)
 {
 nomParam.replace(0,nomStrat.length()+2,"");
 fRouteur->setValeurParametre(nomParam,val);
 }
}
