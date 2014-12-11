//
// Classe d'AmibeMutationIrradiation2
//

#include "AmibeMutationIrradiation2.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeMutationIrradiation2::AmibeMutationIrradiation2(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeMutationIrradiation2";
fCommentaire="AmibeMutationIrradiation2 de base";
doseMutation["Saine"]=95.;
doseMutation["OAR"]=30.;
widthMutation["Saine"]=1;
widthMutation["OAR"]=1;
fGNA=GenerateurNombresAleatoires::getGenerateurNombresAleatoires();
}

//________________________________________________________
AmibeMutationIrradiation2::~AmibeMutationIrradiation2(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeMutationIrradiation2::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("nbTumorales",nbTumorales);
if(ok)
 {
 ok=j->getData("nbSaines",nbSaines);
 if(ok)
  {
  ok=j->getData("doseFraction",doseFraction);
  if(ok)
   {
   ok=j->getData("nbSainesOriginales",nbSainesOriginales);
   if(ok)
    {
    ok=j->getData("zones",zones);
    }
   }
  }
 }
 
//
return ok;
}

//________________________________________________________
Jeton *AmibeMutationIrradiation2::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeMutationIrradiation2
// Cette methode va modifier deux cartographies:
//

j->getData("nbSaines",nbSaines);
j->getData("nbSainesOriginales",nbSainesOriginales);
j->getData("nbTumorales",nbTumorales);
j->getData("doseFraction",doseFraction);
j->getData("zones",zones);
double xMin=nbSaines.getXMin();
double xMax=nbSaines.getXMax();
int dimX=nbSaines.getDimX();
double yMin=nbSaines.getYMin();
double yMax=nbSaines.getYMax();
int dimY=nbSaines.getDimY();

double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;

if(!j->getData("doseTotaleMut",doseTotaleMut))
 {
 doseTotaleMut.setDimX(dimX);
 doseTotaleMut.setXMin(xMin);
 doseTotaleMut.setXMax(xMax);
 doseTotaleMut.setDimY(dimY);
 doseTotaleMut.setYMin(yMin);
 doseTotaleMut.setYMax(yMax);
 double doseM=0.;
 for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
  {
  for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
   {
   doseTotaleMut.setData(doseM,x,y);
   }
  }
 }
double doseM=0;
double doseFrac=0;
int saines=0;
int sainesOri=0;
int tumorales=0.;
int mutantes=0;
double pMut=0.;
string type="";
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  doseM=0.;
  type="";
  doseTotaleMut.getData(doseM,x,y);
  doseFraction.getData(doseFrac,x,y);
  doseM+=doseFrac;
  nbSaines.getData(saines,x,y);
  nbSainesOriginales.getData(sainesOri,x,y);
  nbTumorales.getData(tumorales,x,y);
  if(saines && sainesOri && doseM>0)
   {
   zones.getData(type,x,y);
   type=type.substr(0,3);
   if(type.substr(0,3)=="OAR") type="OAR";
   if(type!="OAR" && type !="Air")
    {
    type="Saine";
    }
   mutantes=evalMutations(sainesOri,doseM,type);
   if(mutantes)
    {
    if(mutantes > saines)
     {
     mutantes=saines;
     }
    saines-=mutantes;
    tumorales+=mutantes;
    if(tumorales > 10000000)
     {
     tumorales=10000000;
     saines=0;
     }
    nbSaines.setData(saines,x,y);
    nbTumorales.setData(tumorales,x,y);
    }
   if(!saines)
    {
    doseM=0.;
    }
   doseTotaleMut.setData(doseM,x,y);
   }
  }
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
j->setData("doseTotaleMut",doseTotaleMut);
return j;
}

//________________________________________________________
int AmibeMutationIrradiation2::evalMutations(int nb0, double dose,string type)
{
//
// Evaluation du nombre de mutantes
//
double moyenne=nb0*1./(1.+exp((doseMutation[type]-dose)/widthMutation[type]));
int nb=fGNA->getPoisson(moyenne);
//int nb=(int)(moyenne+0.5);
return nb;
}

//________________________________________________________
bool AmibeMutationIrradiation2::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=true;
if(nomParam=="doseMutationSaine")
 {
 doseMutation["Saine"]=valeur;
 }
else if(nomParam=="widthMutationSaine")
 {
 widthMutation["Saine"]=valeur;
 }
else if(nomParam=="doseMutationOAR")
 {
 doseMutation["OAR"]=valeur;
 }
else if(nomParam=="widthMutationOAR")
 {
 widthMutation["OAR"]=valeur;
 }
else
 {
 res=false;
 }
return res;
}
