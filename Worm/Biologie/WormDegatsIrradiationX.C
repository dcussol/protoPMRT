//
// Classe d'WormDegatsIrradiationX
//

#include "WormDegatsIrradiationX.h"
#include <cmath>

using namespace std;

//________________________________________________________
WormDegatsIrradiationX::WormDegatsIrradiationX(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="WormDegatsIrradiationX";
fCommentaire="WormDegatsIrradiationX de base";
alphaSaine=0.5;
betaSaine=0.02;
alphaTumorale=0.35;
betaTumorale=0.01;
fGNA=GenerateurNombresAleatoires::getGenerateurNombresAleatoires();
}

//________________________________________________________
WormDegatsIrradiationX::~WormDegatsIrradiationX(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool WormDegatsIrradiationX::peutOperer(Jeton *j)
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
Jeton *WormDegatsIrradiationX::resoudre(Jeton *j)
{
//
// Methode de resolution de WormDegatsIrradiationX
// Cette methode va ajouter au jeton deux cartographies:
//   cartographie dose de la fraction
//   cartographie dose totale jusqu'a maintenant
//

j->getData("nbSaines",nbSaines);
j->getData("nbTumorales",nbTumorales);
j->getData("doseFraction",doseFraction);
double xMin=nbSaines.getXMin();
double xMax=nbSaines.getXMax();
int dim=nbSaines.getDimX();

double xStep=(xMax-xMin)/dim;
double dose=0;
int saines=0;
int tumorales=0.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 doseFraction.getData(dose,x);
 nbSaines.getData(saines,x);
 if(saines)
  {
  saines=evalDegats(saines,dose,alphaSaine,betaSaine);
  nbSaines.setData(saines,x);
  }
 nbTumorales.getData(tumorales,x);
 if(tumorales)
  {
  tumorales=evalDegats(tumorales,dose,alphaTumorale,betaTumorale);
  nbTumorales.setData(tumorales,x);
  }
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
return j;
}

//________________________________________________________
int WormDegatsIrradiationX::evalDegats(int nb0, double dose, double alpha, double beta)
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
bool WormDegatsIrradiationX::setValeurParametre(string nomParam,double valeur)
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
