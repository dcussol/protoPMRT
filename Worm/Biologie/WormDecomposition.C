//
// Classe d'WormDecomposition
//

#include "WormDecomposition.h"
#include <cmath>

using namespace std;

//________________________________________________________
WormDecomposition::WormDecomposition(void): WormProliferation()
{
//
// Constructeur par defaut
//
fNom="WormDecomposition";
fCommentaire="WormDecomposition de base";
tauxSaine=0.05;
tauxTumorale=0.05;
}

//________________________________________________________
WormDecomposition::~WormDecomposition(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *WormDecomposition::resoudre(Jeton *j)
{
//
// Methode de resolution de WormDecomposition
// Cette methode va modifier deux cartographies:
//

j->getData("nbSaines",nbSaines);
j->getData("nbTumorales",nbTumorales);
double xMin=nbSaines.getXMin();
double xMax=nbSaines.getXMax();
int dim=nbSaines.getDimX();

double xStep=(xMax-xMin)/dim;
int saines=0;
int tumorales=0.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 nbSaines.getData(saines,x);
 nbTumorales.getData(tumorales,x);
 if(saines)
  {
  saines=evalDecomposition(saines,tauxSaine);
  nbSaines.setData(saines,x);
  }
 if(tumorales)
  {
  tumorales=evalDecomposition(saines,tauxTumorale);
  nbTumorales.setData(tumorales,x);
  }
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
return j;
}

//________________________________________________________
int WormDecomposition::evalDecomposition(int nb0, double taux)
{
//
// Evaluation du nombre de mutantes
//
double moyenne=nb0*exp(deltaT*taux);
int nb=fGNA->getPoisson(moyenne);
return nb;
}
