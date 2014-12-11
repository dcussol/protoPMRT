//
// Classe de base d'une RouteurAiguillage
//

#ifndef RouteurAiguillage_h
#define RouteurAiguillage_h

class Etat;
#include "Routeur.h"

#include <map>

using namespace std;

class RouteurAiguillage : public Routeur
{
    protected:
     typedef bool (*fonc)(Etat *);

     map<fonc,Etat *>    fMapSuivants;

    public:
     RouteurAiguillage(void);	
     virtual ~RouteurAiguillage(void);
     
     virtual void setEtatSuivant(fonc f,Etat *e)
      {
      fMapSuivants[f]=e;
      }
     virtual Etat *getEtatSuivant(fonc f)
      {
      return fMapSuivants[f];
      }
     
     virtual Etat *suivant(void);
      
     virtual vector<Etat *> getSuivants(void);
};

#endif    
