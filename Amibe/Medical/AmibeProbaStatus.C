//
// Classe d'AmibeProbaStatus
//

#include "AmibeProbaStatus.h"

using namespace std;

//________________________________________________________
AmibeProbaStatus::AmibeProbaStatus(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeProbaStatus";
fCommentaire="AmibeProbaStatus de base";
}

//________________________________________________________
AmibeProbaStatus::~AmibeProbaStatus(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeProbaStatus::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("SFTumorales",SFTumorales);
if(ok)
 {
 ok=j->getData("SFSaines",SFSaines);
 if(ok)
  {
  ok=j->getData("probaNoMutation",probaNoMutation);
  if(ok)
   {
   ok=j->getData("zones",zones);
   }
  }
 }
//
return ok;
}

//________________________________________________________
Jeton *AmibeProbaStatus::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeProbaStatus
// Cette methode va modifier deux cartographies:
//

j->getData("SFSaines",SFSaines);
j->getData("SFTumorales",SFTumorales);
j->getData("probaNoMutation",probaNoMutation);
j->getData("zones",zones);
double xMin=SFSaines.getXMin();
double xMax=SFSaines.getXMax();
int dimX=SFSaines.getDimX();
double yMin=SFSaines.getYMin();
double yMax=SFSaines.getYMax();
int dimY=SFSaines.getDimY();

double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;

map<string,long int> nbOARMax;
map<string,int> nbTum;
map<string,long int> nbSain;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  }
 }
Status st=kGoodShape;
bool tumControl = (nbTum["Tumeur"]==0); 
int compGradeSaine1 = nbTum["Saines"];
int compGradeSaine2 = 0;
map<string,long int>::iterator it;
for(it=nbOARMax.begin();it!=nbOARMax.end();it++)
 {
 compGradeSaine2+=nbTum[it->first];
 }
 
j->setData("etatAmibe",st);
j->setData("controleTumeur",tumControl);
j->setData("complicationSaines",compGradeSaine1);
j->setData("complicationOAR",compGradeSaine2);
return j;
}


//________________________________________________________
bool AmibeProbaStatus::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=false;
return res;
}

//________________________________________________________
Jeton *AmibeProbaStatus::genereDonnee(Jeton *j)
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
j->setData("SFSainesTotal",sainesTot);
j->setData("SFTumoralesTotal",tumoralesTot);
j->setData("etatAmibe",st);
j->setData("controleTumeur",tumControl);
j->setData("complicationSaines",compGradeSaine1);
j->setData("complicationOAR",compGradeSaine2);
return j;
}
