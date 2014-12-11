//
// Classe d'WormIrradiationX
//

#include "WormIrradiationX.h"
#include <cmath>

using namespace std;

//________________________________________________________
WormIrradiationX::WormIrradiationX(void): WormIrradiation()
{
//
// Constructeur par defaut
//
fNom="WormIrradiationX";
fCommentaire="WormIrradiationX de base";
xCenter=50.;
xWidth=8.;
}

//________________________________________________________
WormIrradiationX::~WormIrradiationX(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *WormIrradiationX::resoudre(Jeton *j)
{
//
// Methode de resolution de WormIrradiationX
// Cette methode va ajouter au jeton deux cartographies:
//   cartographie dose de la fraction
//   cartographie dose totale jusqu'a maintenant
//

j=WormIrradiation::resoudre(j);

j->getData("zones",zones);
double xMin=zones.getXMin();
double xMax=zones.getXMax();
int dim=zones.getDimX();

double xStep=(xMax-xMin)/dim;
double dose=0;
double doseTot=0;
double doseM=0.;
int nbM=0.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 dose=evalDose(x);
 if(x>(xCenter-xWidth/2.) && x< (xCenter+xWidth/2.))
  {
  doseM+=dose;
  nbM++;
  }
 doseFraction.setData(dose,x);
 }
// renormalisation
doseM/=nbM;
double fac=doseParFrac/doseM;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 doseFraction.getData(dose,x);
 dose*=fac;
 doseFraction.setData(dose,x);
 doseTotale.getData(doseTot,x);
 doseTot+=dose;
 doseTotale.setData(doseTot,x);
 }
j->setData("doseFraction",doseFraction);
j->setData("doseTotale",doseTotale);
return j;
}

//________________________________________________________
double WormIrradiationX::evalDose(double x)
{
//
// Evaluation de la dose en fonction de x
//
double doseX=0.;
doseX+=0.25*x*exp(-0.08*x);
if(x<100.)
 {
 double y=100.-x;
 doseX+=0.25*y*exp(-0.08*y);
 }
doseX+=2./(1.+exp((abs(x-xCenter)-xWidth)/1.));
return doseX;
}

//________________________________________________________
bool WormIrradiationX::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=true;
if(nomParam=="xCenter")
 {
 xCenter=valeur;
 }
else if(nomParam=="xWidth")
 {
 xWidth=valeur;
 }
else
 {
 res=WormIrradiation::setValeurParametre(nomParam,valeur);
 }
return res;
}
