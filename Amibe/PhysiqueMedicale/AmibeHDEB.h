//
// Classe d'imagerie du Amibe
//

#ifndef AmibeHDEB_h
#define AmibeHDEB_h

#include "Strategie.h"
#include "CartographieVecteur.h"

class AmibeHDEB : public Strategie
{
    protected:
     CartographieVecteur<double> SFSaines;
     CartographieVecteur<double> SFTumorales;
     CartographieVecteur<double> probaNoMutation;
     CartographieVecteur<string> zones;

     map<string,vector<double>*>  vHDMort;
     map<string,vector<double>*>  vHDMut;

  public:
     AmibeHDEB(void);
     ~AmibeHDEB(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
    
     virtual bool setValeurParametre(string nomParam,double valeur);
	 
};

#endif
