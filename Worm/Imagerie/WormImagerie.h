//
// Classe d'imagerie du Worm
//

#ifndef WormImagerie_h
#define WormImagerie_h

#include "Strategie.h"

class WormImagerie : public Strategie
{

    public:
     WormImagerie(void);
     ~WormImagerie(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j) {return true;}
     virtual Jeton *genereDonnee(Jeton *j);
	 
};

#endif
