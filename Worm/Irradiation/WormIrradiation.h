//
// Classe d'imagerie du Worm
//

#ifndef WormIrradiation_h
#define WormIrradiation_h

#include "Strategie.h"
#include "CartographieVecteur.h"

class WormIrradiation : public Strategie
{
    protected:
     double doseParFrac;
     int    nombreDeFrac;
     double doseTraitement;

     CartographieVecteur<double> doseFraction;
     CartographieVecteur<double> doseTotale;
     CartographieVecteur<string> zones;

   public:
     WormIrradiation(void);
     ~WormIrradiation(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     virtual Jeton *genereDonnee(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);
     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["doseParFrac"]=doseParFrac;
      return lstParam;}

};

#endif
