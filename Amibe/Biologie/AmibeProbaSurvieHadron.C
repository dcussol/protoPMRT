//
// Classe d'AmibeProbaSurvieHadron
//

#include "AmibeProbaSurvieHadron.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeProbaSurvieHadron::AmibeProbaSurvieHadron(void): 
AmibeProbaSurvieX()
{
//
// Constructeur par defaut
//
fNom="AmibeProbaSurvieHadron";
fCommentaire="AmibeProbaSurvieHadron de base";
}

//________________________________________________________
AmibeProbaSurvieHadron::~AmibeProbaSurvieHadron(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeProbaSurvieHadron::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=AmibeProbaSurvieX::peutOperer(j);
if(ok)
 {
 ok=j->getData("EBRalpha",EBRalpha);
 }
//
return ok;
}

//________________________________________________________
Jeton *AmibeProbaSurvieHadron::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeProbaSurvieHadron
// Cette methode va ajouter au jeton deux cartographies:
//   cartographie dose de la fraction
//   cartographie dose totale jusqu'a maintenant
//

j->getData("doseFraction",doseFraction);
j->getData("zones",zones);
j->getData("EBRalpha",EBRalpha);
double xMin=zones.getXMin();
double xMax=zones.getXMax();
int dimX=zones.getDimX();
double yMin=zones.getYMin();
double yMax=zones.getYMax();
int dimY=zones.getDimY();

double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;

string zone="unkown";

if(!j->getData("SFSaines",SFSaines) && !j->getData("SFTumorales",SFTumorales))
 {
 cout << "AmibeProbaSurvieHadron: Creation de SFSaines..." << endl;
 SFSaines.setDimX(dimX);
 SFSaines.setXMin(xMin);
 SFSaines.setXMax(xMax);
 SFSaines.setDimY(dimY);
 SFSaines.setYMin(yMin);
 SFSaines.setYMax(yMax);
 SFTumorales.setDimX(dimX);
 SFTumorales.setXMin(xMin);
 SFTumorales.setXMax(xMax);
 SFTumorales.setDimY(dimY);
 SFTumorales.setYMin(yMin);
 SFTumorales.setYMax(yMax);
 for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
  {
  for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
   {
   double val=0.;
   zones.getData(zone,x,y);
   if(zone!="Air")
    {
    if(zone=="Tumeur")
     {
     SFSaines.setData(val,x,y);
     val=1.;
     SFTumorales.setData(val,x,y);
     }
    else
     {
     SFTumorales.setData(val,x,y);
     val=1.;
     SFSaines.setData(val,x,y);
     }
    }
   else
    {
    SFTumorales.setData(val,x,y);
    SFSaines.setData(val,x,y);
    }
   }
  }
 }

double dose=0;
double saines=0;
double tumorales=0;
double EBR=1.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  doseFraction.getData(dose,x,y);
  saines=0;
  tumorales=0;
  EBR=1.;
  if(dose)
   {
   EBRalpha.getData(EBR,x,y);
   SFSaines.getData(saines,x,y);
   if(saines)
    {
    saines*=getSurvivalFactor(dose,EBR*alphaSaine,betaSaine);
    SFSaines.setData(saines,x,y);
    }
   SFTumorales.getData(tumorales,x,y);
   if(tumorales)
    {
    tumorales*=getSurvivalFactor(dose,EBR*alphaTumorale,betaTumorale);
    SFTumorales.setData(tumorales,x,y);
    }
   }
  }
 }

j->setData("SFSaines",SFSaines);
j->setData("SFTumorales",SFTumorales);
return j;
}

