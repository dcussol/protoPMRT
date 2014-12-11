//
// Classe de base d'un probleme
//

#ifndef Etat_h
#define Etat_h

#include "Jeton.h"
#include "FabriqueStrategie.h"
#include "Visiteur.h"
#include "Routeur.h"
class  Automate;
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Etat
{
    protected:
     string           fNom;
     string           fCommentaire;
     string           fTypeEtat;

     Jeton	       *fJeton;
     FabriqueStrategie *fFabStrategie;
     Visiteur          *fVisiteur;
     Routeur	       *fRouteur;
     Strategie	       *fStrategie;
     
     string	                        fNomStrategie;
     map<string, map<string,double> >	fParametresStrategie;
     
     bool		fTested;
     string	        fBackgroundColor;

    public:
     Etat(void);	
     virtual ~Etat(void);
     
     static Etat *construire(void) {return new Etat();}

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

     virtual void setNomStrategie(string nom)
      {
      fNomStrategie=nom;
      }
     virtual string getNomStrategie(void)
      {
      return fNomStrategie;
      }
     virtual Strategie *getStrategie(void)
      {
      return fStrategie;
      }

     virtual void setJeton(Jeton *j)
      {
      fJeton=j;
      }
     virtual Jeton *getJeton(void)
      {
      return fJeton;
      }

     virtual void setFabriqueStrategie(FabriqueStrategie *fabstrat)
      {
      fFabStrategie=fabstrat;
      }
     virtual FabriqueStrategie *getFabriqueStrategie(void)
      {
      return fFabStrategie;
      }

     virtual void setVisiteur(Visiteur *v)
      {
      fVisiteur=v;
      }
     virtual Visiteur *getVisiteur(void)
      {
      return fVisiteur;
      }
    
     virtual void setRouteur(Routeur *r)
      {
      fRouteur=r;
      fRouteur->setEtat(this);
      }
     virtual Routeur *getRouteur(void)
      {
      return fRouteur;
      }
    
     virtual void setTeste(bool t)
      {
      fTested=t;
      }
     virtual bool estTeste(void)
      {
      return fTested;
      }
    
     virtual string getTypeEtat(void)
      {
      return fTypeEtat;
      }

     virtual Jeton *traitement(void);
     virtual Jeton *testeTraitement(bool &ok);

     virtual Etat *suivant(void);
     virtual vector<Etat *> getSuivants(void);
     
     virtual void setParametresStrategie(Strategie *s);
     
     virtual double getValeurParametre(string nomParam);
     virtual void setValeurParametre(string nomParam, double val);
     virtual void resetValeurParametres(void)
      {
      fParametresStrategie.clear();
      }

     virtual void lireFichierConfiguration(istream &fin,Automate *a);
     virtual void ecrireFichierConfiguration(ostream &fout=cout);
     virtual void ecrireDotFile(ostream &fout=cout);

     virtual map<string,double> getValeursParametres(void); 
};

#endif    
