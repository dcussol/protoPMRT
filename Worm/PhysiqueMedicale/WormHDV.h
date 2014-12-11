//
// Classe d'imagerie du Worm
//

#ifndef WormHDV_h
#define WormHDV_h

#include "Strategie.h"
#include "CartographieVecteur.h"

class WormHDV : public Strategie
{
    protected:
     CartographieVecteur<double> doseTotale;
     CartographieVecteur<string> zones;
     double			 doseTraitement;

     map<string,vector<double>*>  vHDV;

  public:
     WormHDV(void);
     ~WormHDV(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
    
     virtual bool setValeurParametre(string nomParam,double valeur);
	 
};

#endif
