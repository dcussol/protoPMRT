//
// Classe d'AmibeIrradiationCarbone
//

#include "AmibeIrradiationCarbone.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeIrradiationCarbone::AmibeIrradiationCarbone(void): AmibeIrradiationProton()
{
//
// Constructeur par defaut
//
fNom="AmibeIrradiationCarbone";
fCommentaire="AmibeIrradiationCarbone de base";
fEBR.clear();
fEBR["EBRplateau"]=1.5;
fEBR["EBRqueue"]=1.;
fEBR["EBRtumeur"]=3.;
fXCentre=50.;
fYCentre=50.;
fNomFichierFaisceaux="FichierFaisceauxCarbone.txt";
this->lireFichierFaisceaux();
}

//________________________________________________________
AmibeIrradiationCarbone::~AmibeIrradiationCarbone(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *AmibeIrradiationCarbone::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeIrradiationCarbone
// Cette methode va ajouter au jeton trois cartographies:
//   cartographie dose de la fraction
//   cartographie dose totale jusqu'a maintenant
//   cartographie des EBRalpha
//
j=AmibeIrradiation::resoudre(j);

j->getData("zones",zones);
double xMin=zones.getXMin();
double xMax=zones.getXMax();
int dimX=zones.getDimX();
double yMin=zones.getYMin();
double yMax=zones.getYMax();
int dimY=zones.getDimY();

bool ok=j->getData("EBRalpha",EBRalpha);
if(!(ok && (EBRalpha.getDimX() == dimX && EBRalpha.getDimX() == dimY))) 
 {
 //cout << "Init EBRTotale" << endl;
 EBRalpha.setDimX(dimX);
 EBRalpha.setXMin(xMin);
 EBRalpha.setXMax(xMax);
 EBRalpha.setDimY(dimY);
 EBRalpha.setYMin(yMin);
 EBRalpha.setYMax(yMax);
 }

double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;
double dose=0;
double doseTot=0;
double EBR=1.;
double sumEBR=0.;
double r0=40;
double rTum=9;
string zone="unknown";
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  zones.getData(zone,x,y);
  doseTot=0.;
  sumEBR=0.;
  for(int i=0;i<fFaisceaux.size();i++)
   {
   tuple<double,double,double> faisceau=fFaisceaux[i];
   double poids=get<0>(faisceau);
   double theta=get<1>(faisceau);
   double largeur=get<2>(faisceau);
   double r=0.;
   EBR=1.;
   dose=0.;
   double rMin=30;
   double rMax=50;
   if(getRfromXYThetaL(r,x,y,r0,theta,largeur) && zone!="Air")
    {
    double xp=x-fXCentre;
    double yp=y-fYCentre;
    double thetap=theta*(acos((double)-1.)/(double)180.0);
    double l=xp*cos(thetap)+yp*sin(thetap);
    double h=-xp*sin(thetap)+yp*cos(thetap);
    l=sqrt(rTum*rTum-h*h);
    rMin=40.-l;
    rMax=40.+l;
    double fac=2.05+0.95*abs(h)/rTum;
    dose=doseParFrac/fac;
    EBR=fEBR["EBRplateau"];
    if(r>=rMin && r < rMax)
     {
     dose=doseParFrac;
     EBR=fEBR["EBRtumeur"];
     }  
    if(r >= rMax)
     {
     EBR=fEBR["EBRqueue"]; 
     double facq=(100-r)/(100-50.);
     if(facq < 0) facq=0.;
     if(facq > 1) facq=1.;
     dose=doseParFrac/(3.+fac)*facq; 
     }
    }
   doseTot+=poids*dose;
   sumEBR+=poids*dose*EBR;
   }
  EBR=1.;
  if(doseTot>0)
   {
   EBR=sumEBR/doseTot;
   }
  dose=doseTot;
  doseFraction.setData(dose,x,y);
  doseTotale.getData(doseTot,x,y);
  doseTot+=dose;
  doseTotale.setData(doseTot,x,y);
  EBRalpha.setData(EBR,x,y);
  }
 }
 
 
j->setData("doseFraction",doseFraction);
j->setData("doseTotale",doseTotale);
j->setData("EBRalpha",EBRalpha);

return j;
}
