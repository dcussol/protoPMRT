//
// Classe d'WormMutationIrradiation
//

#include "WormMutationIrradiation.h"
#include <cmath>

using namespace std;

//________________________________________________________
WormMutationIrradiation::WormMutationIrradiation(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="WormMutationIrradiation";
fCommentaire="WormMutationIrradiation de base";
doseMutation=5.25;
widthMutation=0.2;
fGNA=GenerateurNombresAleatoires::getGenerateurNombresAleatoires();
}

//________________________________________________________
WormMutationIrradiation::~WormMutationIrradiation(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool WormMutationIrradiation::peutOperer(Jeton *j)
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
   }
  }
 }
 
//
return ok;
}

//________________________________________________________
Jeton *WormMutationIrradiation::resoudre(Jeton *j)
{
//
// Methode de resolution de WormMutationIrradiation
// Cette methode va modifier deux cartographies:
//

j->getData("nbSaines",nbSaines);
j->getData("nbSainesOriginales",nbSainesOriginales);
j->getData("nbTumorales",nbTumorales);
j->getData("doseFraction",doseFraction);
double xMin=nbSaines.getXMin();
double xMax=nbSaines.getXMax();
int dim=nbSaines.getDimX();

if(!j->getData("probMutation",probMutation))
 {
 probMutation.setDimX(dim);
 probMutation.setXMin(xMin);
 probMutation.setXMax(xMax);
 }
double xStep=(xMax-xMin)/dim;
double dose=0;
int saines=0;
int sainesOri=0;
int tumorales=0.;
int mutantes=0;
double pMut=0.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 doseFraction.getData(dose,x);
 nbSaines.getData(saines,x);
 nbSainesOriginales.getData(sainesOri,x);
 nbTumorales.getData(tumorales,x);
 pMut=1./(1.+exp((doseMutation-dose)/widthMutation));
 probMutation.setData(pMut,x);
 if(saines && sainesOri)
  {
  mutantes=evalMutations(sainesOri,dose);
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
   nbSaines.setData(saines,x);
   nbTumorales.setData(tumorales,x);
   }
  }
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
j->setData("probMutation",probMutation);
return j;
}

//________________________________________________________
int WormMutationIrradiation::evalMutations(int nb0, double dose)
{
//
// Evaluation du nombre de mutantes
//
double moyenne=nb0*1./(1.+exp((doseMutation-dose)/widthMutation));
int nb=fGNA->getPoisson(moyenne);
//int nb=(int)(moyenne+0.5);
return nb;
}

//________________________________________________________
bool WormMutationIrradiation::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=true;
if(nomParam=="doseMutation")
 {
 doseMutation=valeur;
 }
else if(nomParam=="widthMutation")
 {
 widthMutation=valeur;
 }
else
 {
 res=false;
 }
return res;
}
