//
// Classe d'imagerie du Amibe
//

#ifndef AmibeIrradiationX_h
#define AmibeIrradiationX_h

#include "AmibeIrradiation.h"

class AmibeIrradiationX : public AmibeIrradiation
{
    protected:
     double xCenter;
     double xWidth;

   public:
     AmibeIrradiationX(void);
     ~AmibeIrradiationX(void);
      
     virtual Jeton *resoudre(Jeton *j);
     
     virtual bool setValeurParametre(string nomParam,double valeur);

     virtual double evalDose(double x);
	 
};

#endif
