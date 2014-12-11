//
// Classe de base d'une RouteurSimple
//

#ifndef RouteurSimple_h
#define RouteurSimple_h

class Etat;
#include "Routeur.h"

#include <string>

using namespace std;

class RouteurSimple : public Routeur
{
    protected:
     Etat        *fEtatSuivant;

    public:
     RouteurSimple(void);	
     virtual ~RouteurSimple(void);
     
     static Routeur *construire(void) {new RouteurSimple();}
     
     virtual void setEtatSuivant(Etat *e)
      {
      fEtatSuivant=e;
      }
     virtual Etat *getEtatSuivant(void)
      {
      return fEtatSuivant;
      }
     
     virtual Etat *suivant(void)
      {
      return this->getEtatSuivant();
      }
      
     virtual vector<Etat *> getSuivants(void)
      {
      fSuivants.clear();
      fSuivants.push_back(fEtatSuivant);
      return fSuivants;
      }

     virtual void lireFichierConfiguration(istream &fin,Automate *a);
     virtual void ecrireFichierConfiguration(ostream &fout=cout);
     virtual void ecrireDotFile(ostream &fout=cout);
};

#endif    
