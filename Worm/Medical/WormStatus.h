//
// Classe d'imagerie du Worm
//

#ifndef WormStatus_h
#define WormStatus_h

#include "Strategie.h"
#include "CartographieVecteur.h"

class WormStatus : public Strategie
{
    protected:
     CartographieVecteur<int>    nbSaines;
     CartographieVecteur<int>    nbTumorales;
     CartographieVecteur<string> zones;

  public:
    enum Status
       {kGoodShape,kSick,kDead};

  public:
     WormStatus(void);
     ~WormStatus(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     virtual Jeton *genereDonnee(Jeton *j);
    
     virtual bool setValeurParametre(string nomParam,double valeur);
	 
};

#endif
