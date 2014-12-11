//
// Classe d'imagerie du Amibe
//

#ifndef AmibeProbaMutation2_h
#define AmibeProbaMutation2_h

#include "Strategie.h"
#include "CartographieVecteur.h"

class AmibeProbaMutation2 : public Strategie
{
    protected:
     map<string,double> doseMutation;
     map<string,double> widthMutation;

     CartographieVecteur<string> zones;
     CartographieVecteur<double> doseTotale;
     CartographieVecteur<double> probaNoMutation;

   public:
     AmibeProbaMutation2(void);
     ~AmibeProbaMutation2(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);

     virtual double getProbaMutation(double dose,string type);

     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["doseMutationSaine"]=doseMutation["Saine"];
      lstParam["widthMutationSaine"]=widthMutation["Saine"];
      lstParam["doseMutationOAR"]=doseMutation["OAR"];
      lstParam["widthMutationOAR"]=widthMutation["OAR"];
      return lstParam;}
	 
};

#endif
