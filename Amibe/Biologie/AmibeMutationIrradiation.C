//
// Classe d'AmibeMutationIrradiation
//

#include "AmibeMutationIrradiation.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeMutationIrradiation::AmibeMutationIrradiation(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeMutationIrradiation";
fCommentaire="AmibeMutationIrradiation de base";
doseMutation["Saine"]=5.25;
doseMutation["OAR"]=1.25;
widthMutation["Saine"]=0.115;
widthMutation["OAR"]=0.115;
fGNA=GenerateurNombresAleatoires::getGenerateurNombresAleatoires();
}

//________________________________________________________
AmibeMutationIrradiation::~AmibeMutationIrradiation(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeMutationIrradiation::peutOperer(Jeton *j)
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
Jeton *AmibeMutationIrradiation::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeMutationIrradiation
// Cette methode va modifier deux cartographies:
//

j->getData("nbSaines",nbSaines);
j->getData("nbSainesOriginales",nbSainesOriginales);
j->getData("nbTumorales",nbTumorales);
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
double dose=0;
int saines=0;
int sainesOri=0;
int tumorales=0.;
int mutantes=0;
string type="";
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  doseFraction.getData(dose,x,y);
  nbSaines.getData(saines,x,y);
  nbSainesOriginales.getData(sainesOri,x,y);
  nbTumorales.getData(tumorales,x,y);
  if(saines && sainesOri && dose>0)
   {
   zones.getData(type,x,y);
   if(type.substr(0,3)=="OAR") type="OAR";
   if(type!="OAR" && type !="Air")
    {
    type="Saine";
    }
   mutantes=evalMutations(sainesOri,dose,type);
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
   }
  }
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
return j;
}

//________________________________________________________
int AmibeMutationIrradiation::evalMutations(int nb0, double dose,string type)
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
bool AmibeMutationIrradiation::setValeurParametre(string nomParam,double valeur)
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
