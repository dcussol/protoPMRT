//
// Classe generateur de nombre aleatoires
//

#include "GenerateurNombresAleatoires.h"

#include <chrono>

using namespace std;

GenerateurNombresAleatoires *GenerateurNombresAleatoires::fGNA=0;

//________________________________________________________
GenerateurNombresAleatoires::GenerateurNombresAleatoires(void)
{
//
// Constructeur prive
//
typedef chrono::high_resolution_clock myclock;
myclock::time_point maintenant = myclock::now();
// obtain a seed from the timer
myclock::duration d = maintenant.time_since_epoch();

unsigned mySeed = d.count();

generateur.seed(mySeed);
}

//________________________________________________________
GenerateurNombresAleatoires::~GenerateurNombresAleatoires(void)
{
//
// Destructeur
//
}

//________________________________________________________
double GenerateurNombresAleatoires::getRandom(void)
{
//
// Retourne un nombre aleatoire compris entre 0. et 1.
//
uniform_real_distribution<double> uniforme(0.0,1.0);
double val=uniforme(generateur);
return val;
}

//________________________________________________________
int GenerateurNombresAleatoires::getPoisson(double moyenne)
{
//
// Retourne un nombre aleatoire selon la distribution de Poisson de valeur
// moyenne "moyenne"
//
poisson_distribution<int> poisson(moyenne);
int val=poisson(generateur); 
return val;
}
