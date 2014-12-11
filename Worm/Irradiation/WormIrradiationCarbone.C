//
// Classe d'WormIrradiationCarbone
//

#include "WormIrradiationCarbone.h"
#include <cmath>

using namespace std;

//________________________________________________________
WormIrradiationCarbone::WormIrradiationCarbone(void): WormIrradiationProton1I()
{
//
// Constructeur par defaut
//
fNom="WormIrradiationCarbone";
fCommentaire="WormIrradiationCarbone de base";
fEBR.clear();
fEBR["EBRplateau"]=1.5;
fEBR["EBRqueue"]=1.;
fEBR["EBRtumeur"]=3.;
}

//________________________________________________________
WormIrradiationCarbone::~WormIrradiationCarbone(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *WormIrradiationCarbone::resoudre(Jeton *j)
{
//
// Methode de resolution de WormIrradiationCarbone
// Cette methode va ajouter au jeton trois cartographies:
//   cartographie dose de la fraction
//   cartographie dose totale jusqu'a maintenant
//   cartographie des EBRalpha
//
j=WormIrradiation::resoudre(j);

j->getData("zones",zones);
double xMin=zones.getXMin();
double xMax=zones.getXMax();
int dim=zones.getDimX();

bool ok=j->getData("EBRalpha",EBRalpha);
if(!(ok && (EBRalpha.getDimX() == dim))) 
 {
 //cout << "Init EBRalpha" << endl;
 EBRalpha.setDimX(dim);
 EBRalpha.setXMin(xMin);
 EBRalpha.setXMax(xMax);
 }

double xStep=(xMax-xMin)/dim;
double dose=0;
double doseTot=0;
double EBR=1.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 dose=doseParFrac/2.;
 EBR=fEBR["EBRplateau"];
 if(x>=46 && x < 54)
  {
  dose=doseParFrac;
  EBR=fEBR["EBRtumeur"];
  }  
 if((x-xStep/2.) >= 54 )
  {
  EBR=fEBR["EBRqueue"]; 
  double fac=(100-(x-xStep/2.))/(100-54.);
  if(fac < 0) fac=0.;
  if(fac > 1) fac=1.;
  dose=doseParFrac/4.*fac; 
  }
 doseFraction.setData(dose,x);
 doseTotale.getData(doseTot,x);
 doseTot+=dose;
 doseTotale.setData(doseTot,x);
 EBRalpha.setData(EBR,x);
 }
 
 
j->setData("doseFraction",doseFraction);
j->setData("doseTotale",doseTotale);
j->setData("EBRalpha",EBRalpha);

return j;
}
