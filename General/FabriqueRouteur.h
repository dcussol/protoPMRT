//
// Classe de base d'un FabriqueRouteur
//

#ifndef FabriqueRouteur_h
#define FabriqueRouteur_h

#include "Routeur.h"
#include <string>
#include <map>

using namespace std;

class FabriqueRouteur
{
    protected:
     string           fNom;
     string           fCommentaire;

     typedef Routeur* (*routConst)(void);
     
     map<string,routConst> fConstructeursRouteurs;

     static FabriqueRouteur* gFabriqueRouteur;

     FabriqueRouteur(void);	

    public:

     static FabriqueRouteur* get(void)
      {
      if(!gFabriqueRouteur) gFabriqueRouteur=new FabriqueRouteur();
      return gFabriqueRouteur;
      
      }	
     virtual ~FabriqueRouteur(void);
     
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

     virtual Routeur *fabriqueRouteur(string nomRouteur);
     virtual void ajouteConstructeur(string nomRouteur,Routeur* (*rc)(void));
};   
#endif
