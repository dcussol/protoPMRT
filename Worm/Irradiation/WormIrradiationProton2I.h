//
// Classe d'imagerie du Worm
//

#ifndef WormIrradiationProton2I_h
#define WormIrradiationProton2I_h

#include "WormIrradiationProton1I.h"

class WormIrradiationProton2I : public WormIrradiationProton1I
{
    public:
     WormIrradiationProton2I(void);
     ~WormIrradiationProton2I(void);
      
     virtual Jeton *resoudre(Jeton *j);

};

#endif
