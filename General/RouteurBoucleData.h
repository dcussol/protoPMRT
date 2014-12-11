//
// Classe de base d'une RouteurBoucleData
//

#ifndef RouteurBoucleData_h
#define RouteurBoucleData_h

#include "RouteurBoucle.h"

#include <string>

using namespace std;

class RouteurBoucleData : public RouteurBoucle
{
    protected:
     string     fNomData;

    public:
     RouteurBoucleData(void);	
     virtual ~RouteurBoucleData(void);
     
     static Routeur *construire(void) {return new RouteurBoucleData();}

     virtual void setNomData(string fnd)
      {
      fNomData=fnd;
      }
     virtual string getNomData(void)
      {
      return fNomData;
      }
     
     virtual Etat *suivant(void);

     virtual void lireFichierConfiguration(istream &fin,Automate *a);
     virtual void ecrireFichierConfiguration(ostream &fout=cout);
     virtual void ecrireDotFile(ostream &fout=cout);
};

#endif    
