//
// Classe d'WormIrradiationProton2I
//

#include "WormIrradiationProton2I.h"
#include <cmath>

using namespace std;

//________________________________________________________
WormIrradiationProton2I::WormIrradiationProton2I(void): WormIrradiationProton1I()
{
//
// Constructeur par defaut
//
fNom="WormIrradiationProton2I";
fCommentaire="WormIrradiationProton2I de base";
}

//________________________________________________________
WormIrradiationProton2I::~WormIrradiationProton2I(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *WormIrradiationProton2I::resoudre(Jeton *j)
{
//
// Methode de resolution de WormIrradiationProton2I
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
 //cout << "Init EBRTotale" << endl;
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
 dose=doseParFrac/4.;
 EBR=fEBR["EBRplateau"];
 if(x>=46 && x < 54)
  {
  dose=doseParFrac;
  EBR=fEBR["EBRtumeur"];
  }  
 if((x >= 44 && x < 46.) || (x >= 54 && x < 56.))
  {
  dose=0.75*doseParFrac;
  EBR=fEBR["EBRpenombre"];
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

