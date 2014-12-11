//
// Classe de base d'une Automate
//

#ifndef Automate_h
#define Automate_h

#include "FabriqueEtat.h"
#include "FabriqueRouteur.h"
#include "Etat.h"
#include "Jeton.h"
#include "Visiteur.h"
#include <string>
#include <iostream>
#include <set>

using namespace std;

class Automate
{
    protected:
     string           fNom;
     string           fCommentaire;
     
     Etat        *fEtatInitial;
     Etat 	 *fEtatCourant;
     Jeton 	 *fJeton;

     map<string,Etat *> fVecteurEtats;
     
     set<Visiteur *>    fEnsembleVisiteurs;

     FabriqueEtat       *fFabriqueEtat;
     FabriqueRouteur    *fFabriqueRouteur;

     virtual void initialiseVisiteurs(void);
     virtual void finaliseVisiteurs(void);
     virtual void boucleTraitement(void);

   public:
     Automate(void);	
     virtual ~Automate(void);
     
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

     virtual void setJeton(Jeton *j)
      {
      fJeton=j;
      }
     virtual Jeton *getJeton(void)
      {
      return fJeton;
      }

     virtual void setEtatCourant(Etat *e)
      {
      fEtatCourant=e;
      }
     virtual Etat *getEtatCourant(void)
      {
      return fEtatCourant;
      }
     
     virtual void setEtatInitial(Etat *e)
      {
      fEtatInitial=e;
      }
     virtual Etat *getEtatInitial(void)
      {
      return fEtatInitial;
      }

     virtual void ajouteEtat(Etat *e)
      {
      if(!fVecteurEtats[e->getNom()])
       {
       fVecteurEtats[e->getNom()]=e;
       }
      }

     virtual Etat *getEtat(string nom)
      {
      Etat *e=0;
      map<string,Etat *>::iterator it=fVecteurEtats.find(nom);
      if(it!=fVecteurEtats.end())
       {
       e=it->second;
       }
      return e;
      }
     
     virtual bool testeProcess(void);
     virtual void prepareTest(void);
     virtual void process(void);
     virtual void ecrireFichierConfiguration(ostream &fout=cout);
     virtual void lireFichierConfiguration(istream &fin=cin);
     virtual void ecrireDotFile(ostream &fout=cout);    
     
     virtual map<string,double> getValeursParametres(void); 
     virtual void setValeursParametres(map<string,double> lstParams);

     virtual void setValeurParametre(string nomParam, double val);

     virtual void ajouteConstructeur(string nomEtat,Etat* (*ec)(void))
      {fFabriqueEtat->ajouteConstructeur(nomEtat,ec);}

     virtual void ajouteConstructeur(string nomRouteur,Routeur* (*rc)(void))
      {fFabriqueRouteur->ajouteConstructeur(nomRouteur,rc);}
      
     virtual void printListeEtats(ostream &fout=cout);

friend class EtatAutomate;
};

#endif    
