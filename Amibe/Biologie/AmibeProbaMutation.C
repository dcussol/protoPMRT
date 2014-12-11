//
// Classe d'AmibeProbaMutation
//

#include "AmibeProbaMutation.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeProbaMutation::AmibeProbaMutation(void): Strategie()
{
//
// Constructeur par defaut
//
fCommentaire="AmibeProbaMutation de base";
doseMutation["Saine"]=5.25;
doseMutation["OAR"]=1.25;
widthMutation["Saine"]=0.115;
widthMutation["OAR"]=0.115;
}

//________________________________________________________
AmibeProbaMutation::~AmibeProbaMutation(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeProbaMutation::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("doseFraction",doseFraction);
if(ok)
 {
 ok=j->getData("zones",zones);
 }
 
//
return ok;
}

//________________________________________________________
Jeton *AmibeProbaMutation::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeProbaMutation
// Cette methode va modifier deux cartographies:
//

j->getData("doseFraction",doseFraction);
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
 cout << "Creation de probaNoMutation" << endl;
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
   probMutation=1.;
   zones.getData(type,x,y);
   if(type == "Air")
    probMutation=0.;
   probaNoMutation.setData(probMutation,x,y);
   }
  }
 }

double dose=0;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  doseFraction.getData(dose,x,y);
  zones.getData(type,x,y);
  if(type.substr(0,3)=="OAR") type="OAR";
  if(dose > 0 && type !="Air" && type!="Tumeur")
   {
   probaNoMutation.getData(probMutation,x,y);
   probMutation*=(1.-getProbaMutation(dose,type));
   probaNoMutation.setData(probMutation,x,y);
   }
  }
 }

j->setData("probaNoMutation",probaNoMutation);
return j;
}

//________________________________________________________
double AmibeProbaMutation::getProbaMutation(double dose,string type)
{
//
// Evaluation du nombre de mutantes
//
double moyenne=1./(1.+exp((doseMutation[type]-dose)/widthMutation[type]));
return moyenne;
}

//________________________________________________________
bool AmibeProbaMutation::setValeurParametre(string nomParam,double valeur)
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
