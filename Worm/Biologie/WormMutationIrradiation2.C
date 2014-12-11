//
// Classe d'WormMutationIrradiation2
//

#include "WormMutationIrradiation2.h"
#include <cmath>

using namespace std;

//________________________________________________________
WormMutationIrradiation2::WormMutationIrradiation2(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="WormMutationIrradiation2";
fCommentaire="WormMutationIrradiation2 de base";
doseMutation=95.;
widthMutation=1.;
fGNA=GenerateurNombresAleatoires::getGenerateurNombresAleatoires();
}

//________________________________________________________
WormMutationIrradiation2::~WormMutationIrradiation2(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool WormMutationIrradiation2::peutOperer(Jeton *j)
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
Jeton *WormMutationIrradiation2::resoudre(Jeton *j)
{
//
// Methode de resolution de WormMutationIrradiation2
// Cette methode va modifier deux cartographies:
//

j->getData("nbSaines",nbSaines);
j->getData("nbSainesOriginales",nbSainesOriginales);
j->getData("nbTumorales",nbTumorales);
j->getData("doseFraction",doseFraction);
double xMin=nbSaines.getXMin();
double xMax=nbSaines.getXMax();
int dim=nbSaines.getDimX();
double xStep=(xMax-xMin)/dim;

if(!j->getData("probMutation",probMutation))
 {
 probMutation.setDimX(dim);
 probMutation.setXMin(xMin);
 probMutation.setXMax(xMax);
 }
if(!j->getData("doseTotaleMut",doseTotaleMut))
 {
 doseTotaleMut.setDimX(dim);
 doseTotaleMut.setXMin(xMin);
 doseTotaleMut.setXMax(xMax);
 double doseM=0.;
 for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
  {
  doseTotaleMut.setData(doseM,x);
  }
 }
double doseM=0;
double doseFrac=0;
int saines=0;
int sainesOri=0;
int tumorales=0.;
int mutantes=0;
double pMut=0.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 doseTotaleMut.getData(doseM,x);
 doseFraction.getData(doseFrac,x);
 doseM+=doseFrac;
 nbSaines.getData(saines,x);
 nbSainesOriginales.getData(sainesOri,x);
 nbTumorales.getData(tumorales,x);
 pMut=1./(1.+exp((doseMutation-doseM)/widthMutation));
 probMutation.setData(pMut,x);
 if(saines && sainesOri)
  {
  mutantes=evalMutations(sainesOri,doseM);
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
  if(!saines)
   {
   doseM=0.;
   }
  doseTotaleMut.setData(doseM,x);
  }
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
j->setData("probMutation",probMutation);
j->setData("doseTotaleMut",doseTotaleMut);
return j;
}

//________________________________________________________
int WormMutationIrradiation2::evalMutations(int nb0, double dose)
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
bool WormMutationIrradiation2::setValeurParametre(string nomParam,double valeur)
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
