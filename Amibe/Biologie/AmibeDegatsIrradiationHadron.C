//
// Classe d'AmibeDegatsIrradiationHadron
//

#include "AmibeDegatsIrradiationHadron.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeDegatsIrradiationHadron::AmibeDegatsIrradiationHadron(void): 
AmibeDegatsIrradiationX()
{
//
// Constructeur par defaut
//
fNom="AmibeDegatsIrradiationHadron";
fCommentaire="AmibeDegatsIrradiationHadron de base";
}

//________________________________________________________
AmibeDegatsIrradiationHadron::~AmibeDegatsIrradiationHadron(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeDegatsIrradiationHadron::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=AmibeDegatsIrradiationX::peutOperer(j);
if(ok)
 {
 ok=j->getData("EBRalpha",EBRalpha);
 }
//
return ok;
}

//________________________________________________________
Jeton *AmibeDegatsIrradiationHadron::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeDegatsIrradiationHadron
// Cette methode va ajouter au jeton deux cartographies:
//   cartographie dose de la fraction
//   cartographie dose totale jusqu'a maintenant
//

j->getData("nbSaines",nbSaines);
j->getData("nbTumorales",nbTumorales);
j->getData("doseFraction",doseFraction);
j->getData("EBRalpha",EBRalpha);
double xMin=nbSaines.getXMin();
double xMax=nbSaines.getXMax();
int dimX=nbSaines.getDimX();
double yMin=nbSaines.getYMin();
double yMax=nbSaines.getYMax();
int dimY=nbSaines.getDimY();

double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;

double dose=0;
int saines=0;
int tumorales=0;
double EBR=1.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  doseFraction.getData(dose,x,y);
  saines=0;
  tumorales=0;
  EBR=1.;
  if(dose)
   {
   EBRalpha.getData(EBR,x,y);
   nbSaines.getData(saines,x,y);
   if(saines)
    {
    saines=evalDegats(saines,dose,EBR*alphaSaine,betaSaine);
    nbSaines.setData(saines,x,y);
    }
   nbTumorales.getData(tumorales,x,y);
   if(tumorales)
    {
    tumorales=evalDegats(tumorales,dose,EBR*alphaTumorale,betaTumorale);
    nbTumorales.setData(tumorales,x,y);
    }
   }
  }
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
return j;
}

