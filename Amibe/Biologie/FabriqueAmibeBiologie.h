//
// Classe de base d'un FabriqueAmibeBiologie
//

#ifndef FabriqueAmibeBiologie_h
#define FabriqueAmibeBiologie_h

#include "FabriqueStrategie.h"
#include <string>
#include <map>

using namespace std;

class FabriqueAmibeBiologie: public  FabriqueStrategie
{
    protected:
     map<string,Strategie *> mapOfStrategies;

    public:
     FabriqueAmibeBiologie(void);	
     virtual ~FabriqueAmibeBiologie(void);
     
     virtual Strategie *fabriqueStrategie(string nomStrategie);
};   
#endif
