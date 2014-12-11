//
// Classe d'AmibeIrradiationX
//

#include "AmibeIrradiationX.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeIrradiationX::AmibeIrradiationX(void): AmibeIrradiation()
{
//
// Constructeur par defaut
//
fNom="AmibeIrradiationX";
fCommentaire="AmibeIrradiationX de base";
fXCentre=50.;
fYCentre=50.;
fNomFichierFaisceaux="FichierFaisceauxX.txt";
this->lireFichierFaisceaux();
}

//________________________________________________________
AmibeIrradiationX::~AmibeIrradiationX(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *AmibeIrradiationX::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeIrradiationX
// Cette methode va ajouter au jeton deux cartographies:
//   cartographie dose de la fraction
//   cartographie dose totale jusqu'a maintenant
//

j=AmibeIrradiation::resoudre(j);

j->getData("zones",zones);
double xMin=zones.getXMin();
double xMax=zones.getXMax();
int dimX=zones.getDimX();
double yMin=zones.getYMin();
double yMax=zones.getYMax();
int dimY=zones.getDimY();

double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;
double dose=0;
string zone="unknown";
double doseTot=0;
double doseM=0.;
int nbM=0;
double r0=40;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  zones.getData(zone,x,y);
  doseTot=0.;
  if(zone == "Tumeur")
   {
   nbM++;
   }
  for(int i=0;i<fFaisceaux.size();i++)
   {
   tuple<double,double,double> faisceau=fFaisceaux[i];
   double poids=get<0>(faisceau);
   double theta=get<1>(faisceau);
   double largeur=get<2>(faisceau);
   double r=0;
   if(getRfromXYThetaL(r,x,y,r0,theta,largeur) && zone!="Air")
    {
    dose=evalDose(r);
    //cout << x << " " << y << " " << theta << " " << r << " " << dose << endl;
    doseTot+=dose;
    if(zone == "Tumeur")
     {
     doseM+=dose;
     }
    }
   }
  doseFraction.setData(doseTot,x,y);
  }
 }
// renormalisation
doseM/=nbM;
double fac=1.;
if(doseM>0) fac=doseParFrac/doseM;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  doseFraction.getData(dose,x,y);
  if(dose>0)
   {
   dose*=fac;
   doseFraction.setData(dose,x,y);
   doseTotale.getData(doseTot,x,y);
   doseTot+=dose;
   doseTotale.setData(doseTot,x,y);
   }
  }
 }
j->setData("doseFraction",doseFraction);
j->setData("doseTotale",doseTotale);
return j;
}

//________________________________________________________
double AmibeIrradiationX::evalDose(double x)
{
//
// Evaluation de la dose en fonction de x
//
double doseX=pow(x,0.1)*exp(-0.025*x);
return doseX;
}

//________________________________________________________
bool AmibeIrradiationX::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=AmibeIrradiation::setValeurParametre(nomParam,valeur);
return res;
}
