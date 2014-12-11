//
// Classe d'AmibeProbaMutation2
//

#include "AmibeProbaMutation2.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeProbaMutation2::AmibeProbaMutation2(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeProbaMutation2";
fCommentaire="AmibeProbaMutation2 de base";
doseMutation["Saine"]=95.;
doseMutation["OAR"]=30.;
widthMutation["Saine"]=1;
widthMutation["OAR"]=1;
}

//________________________________________________________
AmibeProbaMutation2::~AmibeProbaMutation2(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeProbaMutation2::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("doseTotale",doseTotale);
if(ok)
 {
 ok=j->getData("zones",zones);
 }
//
return ok;
}

//________________________________________________________
Jeton *AmibeProbaMutation2::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeProbaMutation2
// Cette methode va modifier deux cartographies:
//

j->getData("doseTotale",doseTotale);
j->getData("zones",zones);
double xMin=zones.getXMin();
double xMax=zones.getXMax();
int dimX=zones.getDimX();
double yMin=zones.getYMin();
double yMax=zones.getYMax();
int dimY=zones.getDimY();

double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;

double probMutation=0.;
string type="";

if(!j->getData("probaNoMutation",probaNoMutation))
 {
 probaNoMutation.setDimX(dimX);
 probaNoMutation.setXMin(xMin);
 probaNoMutation.setXMax(xMax);
 probaNoMutation.setDimY(dimY);
 probaNoMutation.setYMin(yMin);
 probaNoMutation.setYMax(yMax);
 for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
  {
  for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
   {
   probMutation=0.;
   zones.getData(type,x,y);
   if(type!="Air" && type!="Tumeur")
    {
    probMutation=1.;
    }
   probaNoMutation.setData(probMutation,y,y);
   }
  }
 }

double doseM=0;
double pMut=0.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  doseM=0.;
  type="";
  doseTotale.getData(doseM,x,y);
  zones.getData(type,x,y);
  if(type.substr(0,3)=="OAR") type="OAR";
  if(doseM > 0 && type !="Air")
   {
   probaNoMutation.getData(pMut,x,y);
   if(pMut > 0.)
    {
    pMut*=(1.-getProbaMutation(doseM,type));
    }
   else
    {
    pMut=(1.-getProbaMutation(doseM,type));
    }
   probaNoMutation.setData(pMut,x,y);
   }
  }
 }

j->setData("probaNoMutation",probaNoMutation);
return j;
}

//________________________________________________________
double AmibeProbaMutation2::getProbaMutation(double dose,string type)
{
//
// Evaluation du nombre de mutantes
//
double moyenne=1./(1.+exp((doseMutation[type]-dose)/widthMutation[type]));
return moyenne;
}

//________________________________________________________
bool AmibeProbaMutation2::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=true;
if(nomParam=="doseMutationSaine")
 {
 doseMutation["saine"]=valeur;
 }
else if(nomParam=="widthMutationSaine")
 {
 widthMutation["saine"]=valeur;
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
