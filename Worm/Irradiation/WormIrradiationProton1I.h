//
// Classe d'imagerie du Worm
//

#ifndef WormIrradiationProton1I_h
#define WormIrradiationProton1I_h

#include "WormIrradiation.h"

class WormIrradiationProton1I : public WormIrradiation
{
    protected:
     CartographieVecteur<double> EBRalpha;
     
     map<string,double> fEBR;
     
    public:
     WormIrradiationProton1I(void);
     ~WormIrradiationProton1I(void);
      
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
