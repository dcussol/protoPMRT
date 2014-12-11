//
// Classe EtatRouteur
//

#include "EtatRouteur.h"
#include "UtilitairesString.h"
#include "Automate.h"

#include <iostream>

using namespace std;

//________________________________________________________
EtatRouteur::EtatRouteur(void):Etat()
{
//
// Constructeur par defaut
//
fNom="EtatRouteur";
fCommentaire="EtatRouteur de base";
fTypeEtat="EtatRouteur";
fNomStrategie="sans";
fBackgroundColor="gold";
}

//________________________________________________________
EtatRouteur::~EtatRouteur(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *EtatRouteur::traitement(void)
{
//
// Methode de traitement: Pas de traitement
//
 Jeton *j=this->getJeton();
 if(fVisiteur)
  {
  fVisiteur->setEtat(this);
  fVisiteur->preTraitement();
  fVisiteur->postTraitement();
  }
 return j;
}

//________________________________________________________
Jeton *EtatRouteur::testeTraitement(bool &ok)
{
//
// Test de l'automate de la classe EtatRouteur
//
 Jeton *j=this->getJeton();
 ok=true;
 return j;
}

//________________________________________________________
void EtatRouteur::lireFichierConfiguration(istream &fin,Automate *a)
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
  }
 }
a->ajouteEtat(this);
}

//________________________________________________________
void EtatRouteur::ecrireFichierConfiguration(ostream &fout)
{
//
// Ecrire l'etat dans un fichier de configuration
//
fout << "etat " << this->getTypeEtat() << endl;
fout << "nom=" << this->getNom() << endl ;
fout << "commentaire=" << this->getCommentaire() << endl;
if(fVisiteur)
 {
 fout << "visiteur=" << fVisiteur->getNom() << endl;
 }
fout << "--> Fin <--" << endl;
}

//________________________________________________________
void EtatRouteur::ecrireDotFile(ostream &fout)
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
     << fBackgroundColor<<"\">" << e->getTypeEtat() << 
     "</td><td border=\"1\">" << e->getNom() << "</td></tr>" << endl;
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
map<string,double> EtatRouteur::getValeursParametres(void)
{
//
// Retourne la liste des valeurs des parametres
//
map<string,double> lstParams;
map<string,double>::iterator itp;

// Parametres du routeur
Routeur *r=this->getRouteur();
if(r)
 {
 map<string,double> lstParamsRouteur=r->getValeursParametres();
 string prefix="Routeur::";
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
void EtatRouteur::setValeurParametre(string nomParam, double val)
{
//
// ajuste la valeur d'un parametre de la strategie
//
vector<string> splitted=splitString(nomParam,"::");
string nomStrat=splitted[0];
if(nomStrat == "Routeur" && fRouteur)
 {
 nomParam.replace(0,nomStrat.length()+2,"");
 fRouteur->setValeurParametre(nomParam,val);
 }
}

