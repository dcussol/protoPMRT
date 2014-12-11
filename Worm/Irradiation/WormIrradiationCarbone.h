//
// Classe d'imagerie du Worm
//

#ifndef WormIrradiationCarbone_h
#define WormIrradiationCarbone_h

#include "WormIrradiationProton1I.h"

class WormIrradiationCarbone : public WormIrradiationProton1I
{
    public:
     WormIrradiationCarbone(void);
     ~WormIrradiationCarbone(void);
      
     virtual Jeton *resoudre(Jeton *j);

};

#endif
