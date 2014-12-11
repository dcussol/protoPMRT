//
// Classe de base d'un FabriqueAmibeMedical
//

#ifndef FabriqueAmibeMedical_h
#define FabriqueAmibeMedical_h

#include "FabriqueStrategie.h"
#include <string>
#include <map>

using namespace std;

class FabriqueAmibeMedical: public  FabriqueStrategie
{
    protected:
     map<string,Strategie *> mapOfStrategies;

    public:
     FabriqueAmibeMedical(void);	
     virtual ~FabriqueAmibeMedical(void);
     
     virtual Strategie *fabriqueStrategie(string nomStrategie);
};   
#endif
