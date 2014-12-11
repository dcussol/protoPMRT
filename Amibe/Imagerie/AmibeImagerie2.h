//
// Classe d'imagerie du Amibe
//

#ifndef AmibeImagerie2_h
#define AmibeImagerie2_h

#include "Strategie.h"

class AmibeImagerie2 : public Strategie
{

    public:
     AmibeImagerie2(void);
     ~AmibeImagerie2(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j) {return true;}
     virtual Jeton *genereDonnee(Jeton *j);
	 
};

#endif
