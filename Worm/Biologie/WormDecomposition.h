//
// Classe d'imagerie du Worm
//

#ifndef WormDecomposition_h
#define WormDecomposition_h

#include "WormProliferation.h"

class WormDecomposition : public WormProliferation
{
   public:
     WormDecomposition(void);
     ~WormDecomposition(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual int evalDecomposition(int nb0, double taux);
	 
};

#endif
