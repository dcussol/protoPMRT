//
// Classe d'imagerie du Amibe
//

#ifndef AmibeImagerie_h
#define AmibeImagerie_h

#include "Strategie.h"

class AmibeImagerie : public Strategie
{

    public:
     AmibeImagerie(void);
     ~AmibeImagerie(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j) {return true;}
     virtual Jeton *genereDonnee(Jeton *j);
	 
};

#endif
