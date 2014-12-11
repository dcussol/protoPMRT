//
// Classe d'imagerie du Worm
//

#ifndef CopierSainesOriginales_h
#define CopierSainesOriginales_h

#include "Strategie.h"
#include "CartographieVecteur.h"
#include "GenerateurNombresAleatoires.h"

class CopierSainesOriginales : public Strategie
{
    protected:
     CartographieVecteur<int>    nbSaines;
     CartographieVecteur<int>    nbSainesOriginales;

   public:
     CopierSainesOriginales(void);
     ~CopierSainesOriginales(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      return lstParam;}
};

#endif
