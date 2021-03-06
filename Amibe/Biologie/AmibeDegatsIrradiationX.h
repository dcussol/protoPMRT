//
// Classe d'imagerie du Amibe
//

#ifndef AmibeDegatsIrradiationX_h
#define AmibeDegatsIrradiationX_h

#include "Strategie.h"
#include "CartographieVecteur.h"
#include "GenerateurNombresAleatoires.h"

class AmibeDegatsIrradiationX : public Strategie
{
    protected:
     // Parametres du modele "Alpha/Beta"
     double alphaTumorale;
     double betaTumorale;
     double alphaSaine;
     double betaSaine;

     GenerateurNombresAleatoires *fGNA;

     CartographieVecteur<double> doseFraction;
     CartographieVecteur<int>    nbSaines;
     CartographieVecteur<int>    nbTumorales;

   public:
     AmibeDegatsIrradiationX(void);
     ~AmibeDegatsIrradiationX(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);

     virtual int evalDegats(int nb0, double dose, double alpha, double beta);
	 
     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["alphaTumorale"]=alphaTumorale;
      lstParam["betaTumorale"]=betaTumorale;
      lstParam["alphaSaine"]=alphaSaine;
      lstParam["betaSaine"]=betaSaine;
      return lstParam;}
};

#endif
