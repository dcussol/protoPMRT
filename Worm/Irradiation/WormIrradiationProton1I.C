//
// Classe d'WormIrradiationProton1I
//

#include "WormIrradiationProton1I.h"
#include <cmath>

using namespace std;

//________________________________________________________
WormIrradiationProton1I::WormIrradiationProton1I(void): WormIrradiation()
{
//
// Constructeur par defaut
//
fNom="WormIrradiationProton1I";
fCommentaire="WormIrradiationProton1I de base";
fEBR.clear();
fEBR["EBRplateau"]=1.;
fEBR["EBRpenombre"]=1.05;
fEBR["EBRtumeur"]=1.1;
}

//________________________________________________________
WormIrradiationProton1I::~WormIrradiationProton1I(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *WormIrradiationProton1I::resoudre(Jeton *j)
{
//
// Methode de resolution de WormIrradiationProton1I
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
 dose=doseParFrac/2.;
 EBR=fEBR["EBRplateau"];
 if(x>=46 && x < 54)
  {
  dose=doseParFrac;
  EBR=fEBR["EBRtumeur"];
  }  
 if((x >= 44 && x < 46.) || (x >= 54 && x < 56.) )
  {
  dose=0.75*doseParFrac;
  EBR=fEBR["EBRpenombre"];
  }
 if(x >= 56)
  {
  dose=0.;
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

//________________________________________________________
Jeton *WormIrradiationProton1I::genereDonnee(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=true;

WormIrradiation::genereDonnee(j);
j->setData("EBRalpha",EBRalpha);

return j;
}
//________________________________________________________
bool WormIrradiationProton1I::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=false;
if(fEBR.find(nomParam) != fEBR.end())
 {
 fEBR[nomParam]=valeur;
 res=true;
 }
else
 {
 res=WormIrradiation::setValeurParametre(nomParam,valeur);
 }
return res;
}
