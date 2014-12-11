//
// Classe d'imagerie du Amibe
//

#ifndef AmibeIrradiationCarbone_h
#define AmibeIrradiationCarbone_h

#include "AmibeIrradiationProton.h"

class AmibeIrradiationCarbone : public AmibeIrradiationProton
{
    public:
     AmibeIrradiationCarbone(void);
     ~AmibeIrradiationCarbone(void);
      
     virtual Jeton *resoudre(Jeton *j);

};

#endif
