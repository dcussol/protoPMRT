//
// Classe d'imagerie du Worm
//

#ifndef WormDegatsIrradiationHadron_h
#define WormDegatsIrradiationHadron_h

#include "WormDegatsIrradiationX.h"
#include "GenerateurNombresAleatoires.h"

class WormDegatsIrradiationHadron : public WormDegatsIrradiationX
{
    protected:
     CartographieVecteur<double> EBRalpha;
     CartographieVecteur<double> SFsaines;
     CartographieVecteur<double> SFtumorales;

   public:
     WormDegatsIrradiationHadron(void);
     ~WormDegatsIrradiationHadron(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
};

#endif
