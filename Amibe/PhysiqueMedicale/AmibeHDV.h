//
// Classe d'imagerie du Amibe
//

#ifndef AmibeHDV_h
#define AmibeHDV_h

#include "Strategie.h"
#include "CartographieVecteur.h"

class AmibeHDV : public Strategie
{
    protected:
     CartographieVecteur<double> doseTotale;
     CartographieVecteur<string> zones;
     double			 doseTraitement;

     map<string,vector<double>*>  vHDV;

  public:
     AmibeHDV(void);
     ~AmibeHDV(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
    
     virtual bool setValeurParametre(string nomParam,double valeur);
	 
};

#endif
