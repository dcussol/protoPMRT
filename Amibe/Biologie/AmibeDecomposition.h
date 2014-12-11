//
// Classe d'imagerie du Amibe
//

#ifndef AmibeDecomposition_h
#define AmibeDecomposition_h

#include "AmibeProliferation.h"

class AmibeDecomposition : public AmibeProliferation
{
   public:
     AmibeDecomposition(void);
     ~AmibeDecomposition(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual int evalDecomposition(int nb0, double taux);
	 
};

#endif
