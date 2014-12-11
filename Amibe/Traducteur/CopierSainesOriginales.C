//
// Classe d'CopierSainesOriginales
//

#include "CopierSainesOriginales.h"

#include <cmath>

using namespace std;

//________________________________________________________
CopierSainesOriginales::CopierSainesOriginales(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="CopierSainesOriginales";
fCommentaire="CopierSainesOriginales de base";
}

//________________________________________________________
CopierSainesOriginales::~CopierSainesOriginales(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool CopierSainesOriginales::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("nbSaines",nbSaines);
//
return ok;
}

//________________________________________________________
Jeton *CopierSainesOriginales::resoudre(Jeton *j)
{
//
// Methode de resolution de CopierSainesOriginales
// Cette methode va modifier deux cartographies:
//

j->getData("nbSaines",nbSaines);
double xMin=nbSaines.getXMin();
double xMax=nbSaines.getXMax();
int dimX=nbSaines.getDimX();
double yMin=nbSaines.getYMin();
double yMax=nbSaines.getYMax();
int dimY=nbSaines.getDimY();

nbSainesOriginales.setDimX(dimX);
nbSainesOriginales.setXMin(xMin);
nbSainesOriginales.setXMax(xMax);
nbSainesOriginales.setDimY(dimY);
nbSainesOriginales.setYMin(yMin);
nbSainesOriginales.setYMax(yMax);

double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;
int saines=0;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  nbSaines.getData(saines,x,y);
  nbSainesOriginales.setData(saines,x,y);
  }
 }

j->setData("nbSainesOriginales",nbSainesOriginales);

return j;
}
