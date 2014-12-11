//
// Classe d'AmibeProbaSurvieX
//

#include "AmibeProbaSurvieX.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeProbaSurvieX::AmibeProbaSurvieX(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeProbaSurvieX";
fCommentaire="AmibeProbaSurvieX de base";
alphaSaine=0.5;
betaSaine=0.02;
alphaTumorale=0.35;
betaTumorale=0.01;
}

//________________________________________________________
AmibeProbaSurvieX::~AmibeProbaSurvieX(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeProbaSurvieX::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("zones",zones);
if(ok)
 {
 ok=j->getData("doseFraction",doseFraction);
 }

//
return ok;
}

//________________________________________________________
Jeton *AmibeProbaSurvieX::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeProbaSurvieX
// Cette methode va ajouter au jeton deux cartographies:
//   cartographie dose de la fraction
//   cartographie dose totale jusqu'a maintenant
//

j->getData("doseFraction",doseFraction);
j->getData("zones",zones);
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
 cout << "AmibeProbaSurvieX: Creation de SFSaines..." << endl;
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
double saines=0.;
double tumorales=0.;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  doseFraction.getData(dose,x,y);
  SFSaines.getData(saines,x,y);
  if(saines)
   {
   saines*=getSurvivalFactor(dose,alphaSaine,betaSaine);
   SFSaines.setData(saines,x,y);
   }
  SFTumorales.getData(tumorales,x,y);
  if(tumorales)
   {
   tumorales*=getSurvivalFactor(dose,alphaTumorale,betaTumorale);
   SFTumorales.setData(tumorales,x,y);
   }
  }
 }
 
j->setData("SFSaines",SFSaines);
j->setData("SFTumorales",SFTumorales);
return j;
}

//________________________________________________________
double AmibeProbaSurvieX::getSurvivalFactor(double dose, double alpha, double beta)
{
//
// Evaluation de la dose en fonction de x
//
double moyenne=exp(-(alpha+beta*dose)*dose);
return moyenne;
}

//________________________________________________________
bool AmibeProbaSurvieX::setValeurParametre(string nomParam,double valeur)
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
