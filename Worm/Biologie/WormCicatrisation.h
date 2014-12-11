//
// Classe d'imagerie du Worm
//

#ifndef WormCicatrisation_h
#define WormCicatrisation_h

#include "Strategie.h"
#include "CartographieVecteur.h"
#include "GenerateurNombresAleatoires.h"

class WormCicatrisation : public Strategie
{
    protected:
     double probaCicatrisation;

     GenerateurNombresAleatoires *fGNA;

     CartographieVecteur<int>    nbSaines;
     CartographieVecteur<int>    nbTumorales;

   public:
     WormCicatrisation(void);
     ~WormCicatrisation(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);

     virtual int evalCicatrisation(void);
	 
     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["probaCicatrisation"]=probaCicatrisation;
      return lstParam;}
};

#endif
