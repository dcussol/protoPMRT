//
// Classe de base d'une strategie
//

#ifndef Strategie_h
#define Strategie_h

#include "Jeton.h"
#include <string>

using namespace std;

class Strategie
{
    protected:
     string           fNom;
     string           fCommentaire;

    public:
     Strategie(void);	
     virtual ~Strategie(void);
     
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

     virtual Jeton *resoudre(Jeton *j)=0;

     virtual Jeton *testResoudre(Jeton *j,bool &ok);
     virtual bool peutOperer(Jeton *j)=0;
     virtual Jeton *genereDonnee(Jeton *j) {return j;}

     virtual bool setValeurParametre(string nomParam,double valeur) {return false;}
     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; return lstParam;}
};

#endif    
