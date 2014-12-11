//
// Classe d'imagerie du Amibe
//

#ifndef AmibeStatus_h
#define AmibeStatus_h

#include "Strategie.h"
#include "CartographieVecteur.h"

class AmibeStatus : public Strategie
{
    protected:
     CartographieVecteur<int>    nbSaines;
     CartographieVecteur<int>    nbTumorales;
     CartographieVecteur<string> zones;

  public:
    enum Status
       {kGoodShape,kSick,kDead};

  public:
     AmibeStatus(void);
     ~AmibeStatus(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     virtual Jeton *genereDonnee(Jeton *j);
    
     virtual bool setValeurParametre(string nomParam,double valeur);
	 
};

#endif
