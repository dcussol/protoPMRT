//
// Classe d'imagerie du Amibe
//

#ifndef AmibeProbaSurvieX_h
#define AmibeProbaSurvieX_h

#include "Strategie.h"
#include "CartographieVecteur.h"

class AmibeProbaSurvieX : public Strategie
{
    protected:
     // Parametres du modele "Alpha/Beta"
     double alphaTumorale;
     double betaTumorale;
     double alphaSaine;
     double betaSaine;

     CartographieVecteur<double> doseFraction;
     CartographieVecteur<double> SFSaines;
     CartographieVecteur<double> SFTumorales;
     CartographieVecteur<string> zones;

   public:
     AmibeProbaSurvieX(void);
     ~AmibeProbaSurvieX(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);

     virtual double getSurvivalFactor(double dose, double alpha, double beta);
	 
     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["alphaTumorale"]=alphaTumorale;
      lstParam["betaTumorale"]=betaTumorale;
      lstParam["alphaSaine"]=alphaSaine;
      lstParam["betaSaine"]=betaSaine;
      return lstParam;}
};

#endif
