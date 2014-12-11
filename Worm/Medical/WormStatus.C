//
// Classe d'WormStatus
//

#include "WormStatus.h"

using namespace std;

//________________________________________________________
WormStatus::WormStatus(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="WormStatus";
fCommentaire="WormStatus de base";
}

//________________________________________________________
WormStatus::~WormStatus(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool WormStatus::peutOperer(Jeton *j)
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
  ok=j->getData("zones",zones);
  }
 }
//
return ok;
}

//________________________________________________________
Jeton *WormStatus::resoudre(Jeton *j)
{
//
// Methode de resolution de WormStatus
// Cette methode va modifier deux cartographies:
//

j->getData("nbSaines",nbSaines);
j->getData("nbTumorales",nbTumorales);
j->getData("zones",zones);
double xMin=nbSaines.getXMin();
double xMax=nbSaines.getXMax();
int dim=nbSaines.getDimX();

double xStep=(xMax-xMin)/dim;
int saines=0;
int tumorales=0;
int sainesTot=0;
int tumoralesTot=0;
string zone="unknown";
int nbCellMax=dim*10000000;
map<string,int> nbTum;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 nbSaines.getData(saines,x);
 nbTumorales.getData(tumorales,x);
 zones.getData(zone,x);
 sainesTot+=saines;
 tumoralesTot+=tumorales;
 if(tumorales)
  {
  nbTum[zone]++;
  }
 }
Status st=kGoodShape;
if(tumoralesTot)
 {
 st=kSick;
 }
double ratio=((double)sainesTot)/nbCellMax;
if(ratio < 1./3.)
 {
 st=kDead;
 }

bool tumControl = (nbTum["Tumeur"]==0); 
int compGradeSaine1 = nbTum["Saine 1"];
int compGradeSaine2 = nbTum["Saine 2"];

j->setData("nbSainesTotal",sainesTot);
j->setData("nbTumoralesTotal",tumoralesTot);
j->setData("etatWorm",st);
j->setData("controleTumeur",tumControl);
j->setData("complicationSaine1",compGradeSaine1);
j->setData("complicationSaine2",compGradeSaine2);
return j;
}


//________________________________________________________
bool WormStatus::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=false;
return res;
}

//________________________________________________________
Jeton *WormStatus::genereDonnee(Jeton *j)
{
//
// Indique quelles donnee sont generee
//
int sainesTot=0;
int tumoralesTot=0;
Status st=kGoodShape;
bool tumControl=true;;
int compGradeSaine1=0;
int compGradeSaine2=0;
j->setData("nbSainesTotal",sainesTot);
j->setData("nbTumoralesTotal",tumoralesTot);
j->setData("etatWorm",st);
j->setData("controleTumeur",tumControl);
j->setData("complicationSaine1",compGradeSaine1);
j->setData("complicationSaine2",compGradeSaine2);
return j;
}
