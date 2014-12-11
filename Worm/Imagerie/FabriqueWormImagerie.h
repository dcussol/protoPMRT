//
// Classe de base d'un FabriqueWormImagerie
//

#ifndef FabriqueWormImagerie_h
#define FabriqueWormImagerie_h

#include "FabriqueStrategie.h"
#include <string>
#include <map>

using namespace std;

class FabriqueWormImagerie: public  FabriqueStrategie
{
    protected:
     map<string,Strategie *> mapOfStrategies;

    public:
     FabriqueWormImagerie(void);	
     virtual ~FabriqueWormImagerie(void);
     
     virtual Strategie *fabriqueStrategie(string nomStrategie);
};   
#endif
