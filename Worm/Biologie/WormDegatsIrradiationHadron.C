//
// Classe d'WormDegatsIrradiationHadron
//

#include "WormDegatsIrradiationHadron.h"
#include <cmath>

using namespace std;

//________________________________________________________
WormDegatsIrradiationHadron::WormDegatsIrradiationHadron(void): 
WormDegatsIrradiationX()
{
//
// Constructeur par defaut
//
fNom="WormDegatsIrradiationHadron";
fCommentaire="WormDegatsIrradiationHadron de base";
}

//________________________________________________________
WormDegatsIrradiationHadron::~WormDegatsIrradiationHadron(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool WormDegatsIrradiationHadron::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=WormDegatsIrradiationX::peutOperer(j);
if(ok)
 {
 ok=j->getData("EBRalpha",EBRalpha);
 }
//
return ok;
}

//________________________________________________________
Jeton *WormDegatsIrradiationHadron::resoudre(Jeton *j)
{
//
// Methode de resolution de WormDegatsIrradiationHadron
// Cette methode va ajouter au jeton deux cartographies:
//   cartographie dose de la fraction
//   cartographie dose totale jusqu'a maintenant
//

j->getData("nbSaines",nbSaines);
j->getData("nbTumorales",nbTumorales);
j->getData("doseFraction",doseFraction);
j->getData("EBRalpha",EBRalpha);
double xMin=nbSaines.getXMin();
double xMax=nbSaines.getXMax();
int dim=nbSaines.getDimX();

if(!j->getData("SFSaines",SFsaines))
 {
 SFsaines.setDimX(dim);
 SFsaines.setXMin(xMin);
 SFsaines.setXMax(xMax);
 }
if(!j->getData("SFTumorales",SFtumorales))
 {
 SFtumorales.setDimX(dim);
 SFtumorales.setXMin(xMin);
 SFtumorales.setXMax(xMax);
 }

double xStep=(xMax-xMin)/dim;
double dose=0;
int saines=0;
int tumorales=0;
double EBR=1.;
double sfS=0.;
double sfT=0.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 doseFraction.getData(dose,x);
 sfS=1.;
 sfT=1.;
 saines=0;
 tumorales=0;
 EBR=1.;
 if(dose)
  {
  EBRalpha.getData(EBR,x);
  nbSaines.getData(saines,x);
  if(saines)
   {
   saines=evalDegats(saines,dose,EBR*alphaSaine,betaSaine);
   nbSaines.setData(saines,x);
   }
  sfS=exp(-(EBR*alphaSaine+betaSaine*dose)*dose);
  nbTumorales.getData(tumorales,x);
  if(tumorales)
   {
   tumorales=evalDegats(tumorales,dose,EBR*alphaTumorale,betaTumorale);
   nbTumorales.setData(tumorales,x);
   }
  sfT=exp(-(EBR*alphaTumorale+betaTumorale*dose)*dose);
  }
 SFsaines.setData(sfS,x);
 SFtumorales.setData(sfT,x);
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
j->setData("SFSaines",SFsaines);
j->setData("SFTumorales",SFtumorales);
return j;
}

