//
// Classe d'imagerie du Worm
//

#ifndef WormProliferation_h
#define WormProliferation_h

#include "Strategie.h"
#include "CartographieVecteur.h"
#include "GenerateurNombresAleatoires.h"

class WormProliferation : public Strategie
{
    protected:
     double tauxSaine;
     double tauxTumorale;
     double deltaT;

     GenerateurNombresAleatoires *fGNA;

     CartographieVecteur<int>    nbSaines;
     CartographieVecteur<int>    nbTumorales;

   public:
     WormProliferation(void);
     ~WormProliferation(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);

     virtual int evalProliferation(int nb0, double taux);
	 
     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["tauxSaine"]=tauxSaine;
      lstParam["tauxTumorale"]=tauxTumorale;
      lstParam["deltaT"]=deltaT;
      return lstParam;}
};

#endif
