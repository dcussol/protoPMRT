//
// Classe d'imagerie du Worm
//

#ifndef WormMutationIrradiation_h
#define WormMutationIrradiation_h

#include "Strategie.h"
#include "CartographieVecteur.h"
#include "GenerateurNombresAleatoires.h"

class WormMutationIrradiation : public Strategie
{
    protected:
     double doseMutation;
     double widthMutation;

     GenerateurNombresAleatoires *fGNA;

     CartographieVecteur<double> doseFraction;
     CartographieVecteur<int>    nbSaines;
     CartographieVecteur<int>    nbSainesOriginales;
     CartographieVecteur<int>    nbTumorales;
     CartographieVecteur<double>    probMutation;

   public:
     WormMutationIrradiation(void);
     ~WormMutationIrradiation(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);

     virtual int evalMutations(int nb0, double dose);

     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["doseMutation"]=doseMutation;
      lstParam["widthMutation"]=widthMutation;
      return lstParam;}
	 
};

#endif
