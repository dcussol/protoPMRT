//
// Classe d'imagerie du Worm
//

#ifndef WormPropagationTumeur_h
#define WormPropagationTumeur_h

#include "Strategie.h"
#include "CartographieVecteur.h"
#include "GenerateurNombresAleatoires.h"

class WormPropagationTumeur : public Strategie
{
    protected:
     double probaPropagation;

     GenerateurNombresAleatoires *fGNA;

     CartographieVecteur<int>    nbSaines;
     CartographieVecteur<int>    nbTumorales;

   public:
     WormPropagationTumeur(void);
     ~WormPropagationTumeur(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);

     virtual int evalPropag(void);

     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["probaPropagation"]=probaPropagation;
      return lstParam;}
	 
};

#endif
