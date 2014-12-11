//
// Classe d'AmibeDecomposition
//

#include "AmibeDecomposition.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeDecomposition::AmibeDecomposition(void): AmibeProliferation()
{
//
// Constructeur par defaut
//
fNom="AmibeDecomposition";
fCommentaire="AmibeDecomposition de base";
tauxSaine=0.05;
tauxTumorale=0.05;
}

//________________________________________________________
AmibeDecomposition::~AmibeDecomposition(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *AmibeDecomposition::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeDecomposition
// Cette methode va modifier deux cartographies:
//

j->getData("nbSaines",nbSaines);
j->getData("nbTumorales",nbTumorales);
double xMin=nbSaines.getXMin();
double xMax=nbSaines.getXMax();
int dimX=nbSaines.getDimX();
double yMin=nbSaines.getYMin();
double yMax=nbSaines.getYMax();
int dimY=nbSaines.getDimY();

double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;
int saines=0;
int tumorales=0.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=xMin+yStep/2.;y<yMax;y+=yStep)
  {
  nbSaines.getData(saines,x,y);
  nbTumorales.getData(tumorales,x,y);
  if(saines)
   {
   saines=evalDecomposition(saines,tauxSaine);
   nbSaines.setData(saines,x,y);
   }
  if(tumorales)
   {
   tumorales=evalDecomposition(saines,tauxTumorale);
   nbTumorales.setData(tumorales,x,y);
   }
  }
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
return j;
}

//________________________________________________________
int AmibeDecomposition::evalDecomposition(int nb0, double taux)
{
//
// Evaluation du nombre de mutantes
//
double moyenne=nb0*exp(deltaT*taux);
int nb=fGNA->getPoisson(moyenne);
return nb;
}
