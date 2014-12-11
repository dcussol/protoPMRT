//
// Classe d'AmibeStatus
//

#include "AmibeStatus.h"

using namespace std;

//________________________________________________________
AmibeStatus::AmibeStatus(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeStatus";
fCommentaire="AmibeStatus de base";
}

//________________________________________________________
AmibeStatus::~AmibeStatus(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeStatus::peutOperer(Jeton *j)
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
Jeton *AmibeStatus::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeStatus
// Cette methode va modifier deux cartographies:
//

j->getData("nbSaines",nbSaines);
j->getData("nbTumorales",nbTumorales);
j->getData("zones",zones);
double xMin=nbSaines.getXMin();
double xMax=nbSaines.getXMax();
int dimX=nbSaines.getDimX();
double yMin=nbSaines.getYMin();
double yMax=nbSaines.getYMax();
int dimY=nbSaines.getDimY();

double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;
int saines=0;
int tumorales=0;
long int sainesTot=0;
long int tumoralesTot=0;
string zone="unknown";
long int nbCellMax=0;
map<string,long int> nbOARMax;
map<string,int> nbTum;
map<string,long int> nbSain;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  zones.getData(zone,x,y);
  if(zone!="Air")
   {
   nbSaines.getData(saines,x,y);
   nbTumorales.getData(tumorales,x,y);
   sainesTot+=saines;
   tumoralesTot+=tumorales;
   nbCellMax+=10000000;
   if(zone.substr(0,3)=="OAR")
    {
    nbOARMax[zone]+=10000000;
    }
   if(tumorales)
    {
    nbTum[zone]++;
    }
   if(saines)
    {
    nbSain[zone]+=saines;
    }   
   }
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
map<string,long int>::iterator it;
for(it=nbOARMax.begin();it!=nbOARMax.end() && st!=kDead;it++)
 {
 zone=it->first;
 ratio=((double)nbSain[zone])/nbOARMax[zone];
 if(ratio < 0.9)
  {
  st=kDead;
  }
 }
bool tumControl = (nbTum["Tumeur"]==0); 
int compGradeSaine1 = nbTum["Saines"];
int compGradeSaine2 = 0;
for(it=nbOARMax.begin();it!=nbOARMax.end();it++)
 {
 compGradeSaine2+=nbTum[it->first];
 }
 
j->setData("nbSainesTotal",sainesTot);
j->setData("nbTumoralesTotal",tumoralesTot);
j->setData("etatAmibe",st);
j->setData("controleTumeur",tumControl);
j->setData("complicationSaines",compGradeSaine1);
j->setData("complicationOAR",compGradeSaine2);
return j;
}


//________________________________________________________
bool AmibeStatus::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=false;
return res;
}

//________________________________________________________
Jeton *AmibeStatus::genereDonnee(Jeton *j)
{
//
// Indique quelles donnee sont generee
//
long int sainesTot=0;
long int tumoralesTot=0;
Status st=kGoodShape;
bool tumControl=true;;
int compGradeSaine1=0;
int compGradeSaine2=0;
j->setData("nbSainesTotal",sainesTot);
j->setData("nbTumoralesTotal",tumoralesTot);
j->setData("etatAmibe",st);
j->setData("controleTumeur",tumControl);
j->setData("complicationSaines",compGradeSaine1);
j->setData("complicationOAR",compGradeSaine2);
return j;
}
