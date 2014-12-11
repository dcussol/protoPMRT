//
// Classe d'imagerie du Worm
//

#ifndef WormIrradiationX_h
#define WormIrradiationX_h

#include "WormIrradiation.h"

class WormIrradiationX : public WormIrradiation
{
    protected:
     double xCenter;
     double xWidth;

   public:
     WormIrradiationX(void);
     ~WormIrradiationX(void);
      
     virtual Jeton *resoudre(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);

     virtual double evalDose(double x);
	 
};

#endif
