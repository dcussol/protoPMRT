//
// Classe de base d'un FabriqueStrategie
//

#ifndef FabriqueStrategie_h
#define FabriqueStrategie_h

#include "Strategie.h"
#include <string>

using namespace std;

class FabriqueStrategie
{
    protected:
     string           fNom;
     string           fCommentaire;

    public:
     FabriqueStrategie(void);	
     virtual ~FabriqueStrategie(void);
     
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

     virtual Strategie *fabriqueStrategie(string nomStrategie)=0;
};   
#endif
