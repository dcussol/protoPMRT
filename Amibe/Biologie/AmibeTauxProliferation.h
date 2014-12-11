//
// Classe d'imagerie du Amibe
//

#ifndef AmibeTauxProliferation_h
#define AmibeTauxProliferation_h

#include "Strategie.h"
#include "CartographieVecteur.h"

class AmibeTauxProliferation : public Strategie
{
    protected:
     double tauxSaine;
     double tauxTumorale;
     double deltaT;

     CartographieVecteur<double>    SFSaines;
     CartographieVecteur<double>    SFTumorales;
     CartographieVecteur<string>    zones;

   public:
     AmibeTauxProliferation(void);
     ~AmibeTauxProliferation(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);

     virtual double getTauxProliferation(double taux);
	 
     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["tauxSaine"]=tauxSaine;
      lstParam["tauxTumorale"]=tauxTumorale;
      lstParam["deltaT"]=deltaT;
      return lstParam;}
      
};

#endif
