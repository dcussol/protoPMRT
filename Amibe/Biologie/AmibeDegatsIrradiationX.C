//
// Classe d'AmibeDegatsIrradiationX
//

#include "AmibeDegatsIrradiationX.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeDegatsIrradiationX::AmibeDegatsIrradiationX(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeDegatsIrradiationX";
fCommentaire="AmibeDegatsIrradiationX de base";
alphaSaine=0.5;
betaSaine=0.02;
alphaTumorale=0.35;
betaTumorale=0.01;
fGNA=GenerateurNombresAleatoires::getGenerateurNombresAleatoires();
}

//________________________________________________________
AmibeDegatsIrradiationX::~AmibeDegatsIrradiationX(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeDegatsIrradiationX::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("nbTumorales",nbTumorales);
if(ok)
 {
 ok=j->getData("nbSaines",nbSaines);
 }
 if(ok)
  {
  ok=j->getData("doseFraction",doseFraction);
  }
//
return ok;
}

//________________________________________________________
Jeton *AmibeDegatsIrradiationX::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeDegatsIrradiationX
// Cette methode va ajouter au jeton deux cartographies:
//   cartographie dose de la fraction
//   cartographie dose totale jusqu'a maintenant
//

j->getData("nbSaines",nbSaines);
j->getData("nbTumorales",nbTumorales);
j->getData("doseFraction",doseFraction);
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
int tumorales=0.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  doseFraction.getData(dose,x,y);
  nbSaines.getData(saines,x,y);
  if(saines)
   {
   saines=evalDegats(saines,dose,alphaSaine,betaSaine);
   nbSaines.setData(saines,x,y);
   }
  nbTumorales.getData(tumorales,x,y);
  if(tumorales)
   {
   tumorales=evalDegats(tumorales,dose,alphaTumorale,betaTumorale);
   nbTumorales.setData(tumorales,x,y);
   }
  }
 }
 
j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
return j;
}

//________________________________________________________
int AmibeDegatsIrradiationX::evalDegats(int nb0, double dose, double alpha, double beta)
{
//
// Evaluation de la dose en fonction de x
//
double moyenne=nb0*exp(-(alpha+beta*dose)*dose);
int nb=fGNA->getPoisson(moyenne);
//int nb=(int)(moyenne+0.5);
return nb;
}

//________________________________________________________
bool AmibeDegatsIrradiationX::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=true;
if(nomParam=="alphaTumorale")
 {
 alphaTumorale=valeur;
 }
else if(nomParam=="betaTumorale")
 {
 betaTumorale=valeur;
 }
else if(nomParam=="alphaSaine")
 {
 alphaSaine=valeur;
 }
else if(nomParam=="betaSaine")
 {
 betaSaine=valeur;
 }
else
 {
 res=false;
 }
return res;
}
