//
// Classe de base d'un FabriqueEtat
//

#ifndef FabriqueEtat_h
#define FabriqueEtat_h

#include "Etat.h"
#include <string>

using namespace std;

class FabriqueEtat
{
    protected:
     string           fNom;
     string           fCommentaire;

     typedef Etat* (*etatConst)(void);
     
     map<string,etatConst> fConstructeursEtats;

     static FabriqueEtat* gFabriqueEtat;

     FabriqueEtat(void);	

    public:

     static FabriqueEtat* get(void)
      {
      if(!gFabriqueEtat) gFabriqueEtat=new FabriqueEtat();
      return gFabriqueEtat;
      }	

     virtual ~FabriqueEtat(void);
     
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

     virtual Etat *fabriqueEtat(string nomEtat);
     virtual void ajouteConstructeur(string nomRouteur,Etat* (*rc)(void));
};   
#endif
