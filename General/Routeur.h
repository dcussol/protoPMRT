//
// Classe de base d'une Routeur
//

#ifndef Routeur_h
#define Routeur_h

class Etat;
class Automate;

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Routeur
{
    protected:
     string           fNom;
     string           fCommentaire;
     string           fTypeRouteur;

     Etat        *fEtat;
     
     vector<Etat *>  fSuivants;

    public:
     Routeur(void);	
     virtual ~Routeur(void);
     
     virtual void setNom(string nom)
      {
      fNom=nom;
      }
     virtual string getNom(void)
      {
      return fNom;
      }

     virtual void setCommentaire(string comment)
      {
      fCommentaire=comment;
      }
     virtual string getCommentaire(void)
      {
      return fCommentaire;
      }

     virtual void setEtat(Etat *e)
      {
      fEtat=e;
      }
     virtual Etat *getEtat(void)
      {
      return fEtat;
      }
     
     virtual vector<Etat *> getSuivants(void)
      {
      return fSuivants;
      }

     virtual string getTypeRouteur(void)
      {
      return fTypeRouteur;
      }

     virtual Etat *suivant(void)=0;
     virtual void lireFichierConfiguration(istream &fin,Automate *a);
     virtual void ecrireFichierConfiguration(ostream &fout=cout);
     virtual void ecrireDotFile(ostream &fout=cout);
     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; return lstParam;}
      
     virtual void setValeurParametre(string nomParam, double val){;}
};

#endif    
