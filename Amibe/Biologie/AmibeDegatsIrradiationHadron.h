//
// Classe d'imagerie du Amibe
//

#ifndef AmibeDegatsIrradiationHadron_h
#define AmibeDegatsIrradiationHadron_h

#include "AmibeDegatsIrradiationX.h"
#include "GenerateurNombresAleatoires.h"

class AmibeDegatsIrradiationHadron : public AmibeDegatsIrradiationX
{
    protected:
     CartographieVecteur<double> EBRalpha;

   public:
     AmibeDegatsIrradiationHadron(void);
     ~AmibeDegatsIrradiationHadron(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
};

#endif
