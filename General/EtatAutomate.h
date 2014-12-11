//
// Classe de base d'un probleme
//

#ifndef EtatAutomate_h
#define EtatAutomate_h

#include "Automate.h"
#include "Etat.h"
#include <string>

using namespace std;

class EtatAutomate : public Etat
{
    protected:
     Automate    *fAutomate;

    public:
     EtatAutomate(void);	
     virtual ~EtatAutomate(void);

     static Etat *construire(void){return new EtatAutomate();}
     
     virtual void setAutomate(Automate *a)
      {
      fAutomate=a;
      }
     virtual Automate *getAutomate(void)
      {
      return fAutomate;
      }

     virtual void setEtatInitial(Etat *e)
      {
      if(fAutomate) fAutomate->setEtatInitial(e);
      }
     virtual Etat *getEtatInitial(void)
      {
      Etat *e=0;
      if(fAutomate) e=fAutomate->getEtatInitial(); 
      return e;
      }


     virtual Jeton *traitement(void);
     virtual Jeton *testeTraitement(bool &ok);
     virtual void ecrireDotFile(ostream &fout=cout);

     virtual void lireFichierConfiguration(istream &fin,Automate *a);
     virtual void ecrireFichierConfiguration(ostream &fout=cout);
     virtual void setValeurParametre(string nomParam, double val);

     virtual map<string,double> getValeursParametres(void); 
};

#endif    
