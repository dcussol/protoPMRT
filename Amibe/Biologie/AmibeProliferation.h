//
// Classe d'imagerie du Amibe
//

#ifndef AmibeProliferation_h
#define AmibeProliferation_h

#include "Strategie.h"
#include "CartographieVecteur.h"
#include "GenerateurNombresAleatoires.h"

class AmibeProliferation : public Strategie
{
    protected:
     double tauxSaine;
     double tauxTumorale;
     double deltaT;

     GenerateurNombresAleatoires *fGNA;

     CartographieVecteur<int>    nbSaines;
     CartographieVecteur<int>    nbTumorales;
     CartographieVecteur<string>    zones;

   public:
     AmibeProliferation(void);
     ~AmibeProliferation(void);
      
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
      
     virtual void propagSaines(double x,double y,
                               double xStep,double yStep,
			       int exces);
     virtual void propagTumorales(double x,double y,
                               double xStep,double yStep,
			       int exces);
};

#endif
