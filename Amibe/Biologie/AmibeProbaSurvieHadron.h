//
// Classe d'imagerie du Amibe
//

#ifndef AmibeProbaSurvieHadron_h
#define AmibeProbaSurvieHadron_h

#include "AmibeProbaSurvieX.h"
#include "GenerateurNombresAleatoires.h"

class AmibeProbaSurvieHadron : public AmibeProbaSurvieX
{
    protected:
     CartographieVecteur<double> EBRalpha;

   public:
     AmibeProbaSurvieHadron(void);
     ~AmibeProbaSurvieHadron(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     
};

#endif
