//
// Classe d'WormCicatrisation
//

#include "WormCicatrisation.h"

#include <cmath>

using namespace std;

//________________________________________________________
WormCicatrisation::WormCicatrisation(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="WormCicatrisation";
fCommentaire="WormCicatrisation de base";
probaCicatrisation=1.e-5;
fGNA=GenerateurNombresAleatoires::getGenerateurNombresAleatoires();
}

//________________________________________________________
WormCicatrisation::~WormCicatrisation(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool WormCicatrisation::peutOperer(Jeton *j)
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
Jeton *WormCicatrisation::resoudre(Jeton *j)
{
//
// Methode de resolution de WormCicatrisation
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
 nbSaines.getData(saines,x);
 if((saines+tumorales) == 0)
  {
  nouvelles=evalCicatrisation();
  nbSaines.setData(nouvelles,x);
  }
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
return j;
}

//________________________________________________________
int WormCicatrisation::evalCicatrisation(void)
{
//
// Evaluation du nombre de mutantes
//

double moyenne=10000000*probaCicatrisation;
int nb=fGNA->getPoisson(moyenne);
//int nb=(int)(moyenne+0.5);
return nb;
}

//________________________________________________________
bool WormCicatrisation::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=true;
if(nomParam=="probaCicatrisation")
 {
 probaCicatrisation=valeur;
 }
else
 {
 res=false;
 }
return res;
}
