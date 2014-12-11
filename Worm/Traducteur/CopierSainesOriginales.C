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
int dim=nbSaines.getDimX();

nbSainesOriginales.setDimX(dim);
nbSainesOriginales.setXMin(xMin);
nbSainesOriginales.setXMax(xMax);

double xStep=(xMax-xMin)/dim;
int saines=0;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 nbSaines.getData(saines,x);
 nbSainesOriginales.setData(saines,x);
 }

j->setData("nbSainesOriginales",nbSainesOriginales);

return j;
}
