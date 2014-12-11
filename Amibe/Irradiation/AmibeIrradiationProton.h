//
// Classe d'imagerie du Amibe
//

#ifndef AmibeIrradiationProton_h
#define AmibeIrradiationProton_h

#include "AmibeIrradiation.h"

class AmibeIrradiationProton : public AmibeIrradiation
{
    protected:
     CartographieVecteur<double> EBRalpha;
     
     map<string,double> fEBR;
     
    public:
     AmibeIrradiationProton(void);
     ~AmibeIrradiationProton(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual Jeton *genereDonnee(Jeton *j);
     
     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["doseParFrac"]=doseParFrac;
      lstParam.insert(fEBR.begin(),fEBR.end());
      return lstParam;}
      
     virtual bool setValeurParametre(string nomParam,double valeur);
};

#endif
