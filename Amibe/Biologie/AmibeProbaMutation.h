//
// Classe d'imagerie du Amibe
//

#ifndef AmibeProbaMutation_h
#define AmibeProbaMutation_h

#include "Strategie.h"
#include "CartographieVecteur.h"

class AmibeProbaMutation : public Strategie
{
    protected:
     map<string,double> doseMutation;
     map<string,double> widthMutation;

     CartographieVecteur<string> zones;
     CartographieVecteur<double> doseFraction;
     CartographieVecteur<double> probaNoMutation;

   public:
     AmibeProbaMutation(void);
     ~AmibeProbaMutation(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);

     virtual double getProbaMutation(double dose, string type);

     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["doseMutationSaine"]=doseMutation["saine"];
      lstParam["widthMutationSaine"]=widthMutation["saine"];
      lstParam["doseMutationOAR"]=doseMutation["OAR"];
      lstParam["widthMutationOAR"]=widthMutation["OAR"];
      return lstParam;}
	 
};

#endif
