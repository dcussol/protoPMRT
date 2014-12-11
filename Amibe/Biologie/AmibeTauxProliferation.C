//
// Classe d'AmibeTauxProliferation
//

#include "AmibeTauxProliferation.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeTauxProliferation::AmibeTauxProliferation(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeTauxProliferation";
fCommentaire="AmibeTauxProliferation de base";
tauxSaine=1.;
tauxTumorale=0.2;
deltaT=1.;
}

//________________________________________________________
AmibeTauxProliferation::~AmibeTauxProliferation(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeTauxProliferation::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("SFTumorales",SFTumorales);
if(ok)
 {
 ok=j->getData("SFSaines",SFSaines);
 }
//
return ok;
}

//________________________________________________________
Jeton *AmibeTauxProliferation::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeTauxProliferation
// Cette methode va modifier deux cartographies:
//

j->getData("SFSaines",SFSaines);
j->getData("SFTumorales",SFTumorales);
j->getData("zones",zones);
double xMin=SFSaines.getXMin();
double xMax=SFSaines.getXMax();
int dimX=SFSaines.getDimX();
double yMin=SFSaines.getYMin();
double yMax=SFSaines.getYMax();
int dimY=SFSaines.getDimY();

double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;
double saines=0;
double tumorales=0.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  SFSaines.getData(saines,x,y);
  SFTumorales.getData(tumorales,x,y);
  if(tumorales)
   {
   tumorales*=getTauxProliferation(tauxTumorale);
   if(tumorales > 1.)
    {
    tumorales=1.;
    }
   }
  if(saines)
   {
   saines*=getTauxProliferation(tauxSaine);
   if(saines > 1.)
    {
    saines=1.;
    }
   }
  SFSaines.setData(saines,x,y);
  SFTumorales.setData(tumorales,x,y);
  }
 }

j->setData("SFSaines",SFSaines);
j->setData("SFTumorales",SFTumorales);

double ageAmibe=0.;
if(j->getData("ageAmibe",ageAmibe))
 {
 ageAmibe+=deltaT;
 }
else
 {
 ageAmibe=deltaT;
 }
j->setData("ageAmibe",ageAmibe);

return j;
}

//________________________________________________________
double AmibeTauxProliferation::getTauxProliferation(double taux)
{
//
// Evaluation du nombre de mutantes
//
double moyenne=exp(deltaT*taux);
return moyenne;
}

//________________________________________________________
bool AmibeTauxProliferation::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=true;
if(nomParam=="tauxTumorale")
 {
 tauxTumorale=valeur;
 }
else if(nomParam=="tauxSaine")
 {
 tauxSaine=valeur;
 }
else if(nomParam=="deltaT")
 {
 deltaT=valeur;
 }
else
 {
 res=false;
 }
return res;
}
	
