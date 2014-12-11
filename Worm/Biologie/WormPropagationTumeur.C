//
// Classe d'WormPropagationTumeur
//

#include "WormPropagationTumeur.h"
#include <cmath>

using namespace std;

//________________________________________________________
WormPropagationTumeur::WormPropagationTumeur(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="WormPropagationTumeur";
fCommentaire="WormPropagationTumeur de base";
probaPropagation=0.1;
fGNA=GenerateurNombresAleatoires::getGenerateurNombresAleatoires();
}

//________________________________________________________
WormPropagationTumeur::~WormPropagationTumeur(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool WormPropagationTumeur::peutOperer(Jeton *j)
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
Jeton *WormPropagationTumeur::resoudre(Jeton *j)
{
//
// Methode de resolution de WormPropagationTumeur
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
 nbTumorales.getData(tumorales,x);
 if(tumorales == 10000000)
  {
  if(x >= xMin+xStep)
   {
   double xv=x-xStep;
   nbTumorales.getData(tumorales,xv);
   nbSaines.getData(saines,xv);
   if(saines && !tumorales)
    {
    tumorales=evalPropag();
    saines-=tumorales;
    if(saines < 0) saines=0;
    nbSaines.setData(saines,xv);
    nbTumorales.setData(tumorales,xv);
    }
   }
  if(x <= xMax-xStep)
   {
   double xv=x+xStep;
   nbTumorales.getData(tumorales,xv);
   nbSaines.getData(saines,xv);
   if(saines && !tumorales)
    {
    tumorales=evalPropag();
    saines-=tumorales;
    if(saines < 0) saines=0;
    nbSaines.setData(saines,xv);
    nbTumorales.setData(tumorales,xv);
    }
   }
  }
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
return j;
}

//________________________________________________________
int WormPropagationTumeur::evalPropag(void)
{
//
// Evaluation du nombre de mutantes
//
double moyenne=10000000*probaPropagation;
int nb=fGNA->getPoisson(moyenne);
//int nb=(int)(moyenne+0.5);
return nb;
}

//________________________________________________________
bool WormPropagationTumeur::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=true;
if(nomParam=="probaPropagation")
 {
 probaPropagation=valeur;
 }
else
 {
 res=false;
 }
return res;
}
