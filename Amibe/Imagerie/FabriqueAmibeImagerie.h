//
// Classe de base d'un FabriqueAmibeImagerie
//

#ifndef FabriqueAmibeImagerie_h
#define FabriqueAmibeImagerie_h

#include "FabriqueStrategie.h"
#include <string>
#include <map>

using namespace std;

class FabriqueAmibeImagerie: public  FabriqueStrategie
{
    protected:
     map<string,Strategie *> mapOfStrategies;

    public:
     FabriqueAmibeImagerie(void);	
     virtual ~FabriqueAmibeImagerie(void);
     
     virtual Strategie *fabriqueStrategie(string nomStrategie);
};   
#endif
