//
// Classe d'imagerie du Amibe
//

#ifndef AmibeProbaStatus_h
#define AmibeProbaStatus_h

#include "Strategie.h"
#include "CartographieVecteur.h"

class AmibeProbaStatus : public Strategie
{
    protected:
     CartographieVecteur<double> SFSaines;
     CartographieVecteur<double> SFTumorales;
     CartographieVecteur<double> probaNoMutation;
     CartographieVecteur<string> zones;

  public:
    enum Status
       {kGoodShape,kSick,kDead};

  public:
     AmibeProbaStatus(void);
     ~AmibeProbaStatus(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     virtual Jeton *genereDonnee(Jeton *j);
    
     virtual bool setValeurParametre(string nomParam,double valeur);
	 
};

#endif
