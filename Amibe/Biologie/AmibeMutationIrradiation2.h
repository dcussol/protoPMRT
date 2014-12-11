//
// Classe d'imagerie du Amibe
//

#ifndef AmibeMutationIrradiation2_h
#define AmibeMutationIrradiation2_h

#include "Strategie.h"
#include "CartographieVecteur.h"
#include "GenerateurNombresAleatoires.h"

class AmibeMutationIrradiation2 : public Strategie
{
    protected:
     map<string,double> doseMutation;
     map<string,double> widthMutation;

     GenerateurNombresAleatoires *fGNA;

     CartographieVecteur<string> zones;
     CartographieVecteur<double> doseFraction;
     CartographieVecteur<double> doseTotaleMut;
     CartographieVecteur<int>    nbSaines;
     CartographieVecteur<int>    nbSainesOriginales;
     CartographieVecteur<int>    nbTumorales;
     CartographieVecteur<double>    probMutation;

   public:
     AmibeMutationIrradiation2(void);
     ~AmibeMutationIrradiation2(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);

     virtual int evalMutations(int nb0, double dose,string type);

     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["doseMutationSaine"]=doseMutation["Saine"];
      lstParam["widthMutationSaine"]=widthMutation["Saine"];
      lstParam["doseMutationOAR"]=doseMutation["OAR"];
      lstParam["widthMutationOAR"]=widthMutation["OAR"];
      return lstParam;}
	 
};

#endif
