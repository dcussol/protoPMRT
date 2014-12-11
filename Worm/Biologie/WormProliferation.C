//
// Classe d'WormProliferation
//

#include "WormProliferation.h"
#include <cmath>

using namespace std;

//________________________________________________________
WormProliferation::WormProliferation(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="WormProliferation";
fCommentaire="WormProliferation de base";
tauxSaine=1.;
tauxTumorale=0.2;
deltaT=1.;
fGNA=GenerateurNombresAleatoires::getGenerateurNombresAleatoires();
}

//________________________________________________________
WormProliferation::~WormProliferation(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool WormProliferation::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("nbTumorales",nbTumorales);
if(ok)
 {
 ok=j->getData("nbSaines",nbSaines);
 }
//
return ok;
}

//________________________________________________________
Jeton *WormProliferation::resoudre(Jeton *j)
{
//
// Methode de resolution de WormProliferation
// Cette methode va modifier deux cartographies:
//

j->getData("nbSaines",nbSaines);
j->getData("nbTumorales",nbTumorales);
double xMin=nbSaines.getXMin();
double xMax=nbSaines.getXMax();
int dim=nbSaines.getDimX();

double xStep=(xMax-xMin)/dim;
int saines=0;
int tumorales=0.;
int nouvelles=0.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 nbSaines.getData(saines,x);
 nbTumorales.getData(tumorales,x);
 if(tumorales && tumorales < 10000000)
  {
  nouvelles=evalProliferation(tumorales,tauxTumorale);
  tumorales+=nouvelles;
  if(tumorales > 10000000)
   {
   tumorales=10000000;
   }
  if(saines+tumorales > 10000000)
   {
   saines=10000000 - tumorales;
   }
  }
 if(saines && saines < 10000000)
  {
  nouvelles=evalProliferation(saines,tauxSaine);
  saines+=nouvelles;
  if(saines+tumorales > 10000000)
   {
   saines=10000000 - tumorales;
   }
  }
 nbSaines.setData(saines,x);
 nbTumorales.setData(tumorales,x);
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);

double ageWorm=0.;
if(j->getData("ageWorm",ageWorm))
 {
 ageWorm+=deltaT;
 }
else
 {
 ageWorm=deltaT;
 }
j->setData("ageWorm",ageWorm);

return j;
}

//________________________________________________________
int WormProliferation::evalProliferation(int nb0, double taux)
{
//
// Evaluation du nombre de mutantes
//
double moyenne=nb0*(exp(deltaT*taux)-1.);
int nb=fGNA->getPoisson(moyenne);
//int nb=(int)(moyenne+0.5);
return nb;
}

//________________________________________________________
bool WormProliferation::setValeurParametre(string nomParam,double valeur)
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
