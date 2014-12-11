//
// Classe d'AmibeProliferation
//

#include "AmibeProliferation.h"
#include <cmath>

using namespace std;

//________________________________________________________
AmibeProliferation::AmibeProliferation(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeProliferation";
fCommentaire="AmibeProliferation de base";
tauxSaine=1.;
tauxTumorale=0.2;
deltaT=1.;
fGNA=GenerateurNombresAleatoires::getGenerateurNombresAleatoires();
}

//________________________________________________________
AmibeProliferation::~AmibeProliferation(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeProliferation::peutOperer(Jeton *j)
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
Jeton *AmibeProliferation::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeProliferation
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
int tumorales=0.;
int nouvelles=0.;
int excesTum=0;
int excesSain=0;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  nbSaines.getData(saines,x,y);
  nbTumorales.getData(tumorales,x,y);
  excesTum=0;
  if(tumorales && tumorales < 10000000)
   {
   nouvelles=evalProliferation(tumorales,tauxTumorale);
   tumorales+=nouvelles;
   if(tumorales > 10000000)
    {
    excesTum=tumorales-10000000;
    tumorales=10000000;
    propagTumorales(x,y,xStep,yStep,excesTum); 
    }
   if(saines+tumorales > 10000000)
    {
    saines=10000000 - tumorales;
    }
   }
  if(saines && saines < 10000000)
   {
   nouvelles=evalProliferation(saines,tauxSaine);
   saines+=nouvelles;
   if(saines+tumorales > 10000000)
    {
    excesSain=saines-(10000000 - tumorales);
    saines=10000000 - tumorales;
    propagSaines(x,y,xStep,yStep,excesSain); 
    }
   }
  nbSaines.setData(saines,x,y);
  nbTumorales.setData(tumorales,x,y);
  }
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);

double ageAmibe=0.;
if(j->getData("ageAmibe",ageAmibe))
 {
 ageAmibe+=deltaT;
 }
else
 {
 ageAmibe=deltaT;
 }
j->setData("ageAmibe",ageAmibe);

return j;
}

//________________________________________________________
int AmibeProliferation::evalProliferation(int nb0, double taux)
{
//
// Evaluation du nombre de mutantes
//
double moyenne=nb0*(exp(deltaT*taux)-1.);
int nb=fGNA->getPoisson(moyenne);
//int nb=(int)(moyenne+0.5);
return nb;
}

//________________________________________________________
bool AmibeProliferation::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=true;
if(nomParam=="tauxTumorale")
 {
 tauxTumorale=valeur;
 }
else if(nomParam=="tauxSaine")
 {
 tauxSaine=valeur;
 }
else if(nomParam=="deltaT")
 {
 deltaT=valeur;
 }
else
 {
 res=false;
 }
return res;
}

//________________________________________________________
void AmibeProliferation::propagSaines(double x,double y,
		                      double xStep,double yStep,
   		                      int exces)
{
//
// Propagation des cellules saines sur les voxels voisins
// les cellules saines se propagent si il n'y a aucune cellule
// dans les voxels voisins
//
// Comptage des voxels voisins vides
int saines=0;
int tumorales=0;
string zone="";
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};

// Comptage des voxels voisins vides
vector<int> vides;
for(int i=0;i<4;i++)
 {
 nbSaines.getData(saines,x+dx[i]*xStep,y+dy[i]*yStep);
 nbTumorales.getData(tumorales,x+dx[i]*xStep,y+dy[i]*yStep);
 zones.getData(zone,x+dx[i]*xStep,y+dy[i]*yStep);
 if(tumorales==0 && zone!="Air")
  {
  vides.push_back(i);
  }
 }

// Propagation des cellules saines sur les voisines
int nbVides=vides.size();
if(nbVides)
 {
 double moyenne=exces/nbVides;
 int dec=(int)(nbVides*fGNA->getRandom());
 for(int j=0;j<nbVides-1;j++)
  {
  int i=vides[(j+dec)%nbVides];
  nbSaines.getData(saines,x+dx[i]*xStep,y+dy[i]*yStep);
  int cic=fGNA->getPoisson(moyenne);
  if(saines+cic>10000000) cic=10000000-saines;
  if(cic>exces) cic=exces;
  if(cic) 
   {
   saines+=cic;
   nbSaines.setData(saines,x+dx[i]*xStep,y+dy[i]*yStep);
   exces-=cic;
   }
  }
 if(exces)
  {
  int i=vides[(nbVides-1+dec)%nbVides];
  nbSaines.getData(saines,x+dx[i]*xStep,y+dy[i]*yStep);
  if(saines+exces>10000000) exces=10000000-saines;
  saines+=exces;
  nbSaines.setData(saines,x+dx[i]*xStep,y+dy[i]*yStep);
  }
 }
}

//________________________________________________________
void AmibeProliferation::propagTumorales(double x,double y,
                                         double xStep,double yStep,
			                 int exces)
{
//
// Propagation des cellules tumorales sur les voxels voisins
// les cellules tumorales se propagent si le voisin n'a pas 
// un maximum de cellules tumorales
int saines=0;
int tumorales=0;
string zone="";
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};

// Comptage des voxels voisins possibles
vector<int> possibles;
for(int i=0;i<4;i++)
 {
 zones.getData(zone,x+dx[i]*xStep,y+dy[i]*yStep);
 if(zone != "Air")
  {
  nbTumorales.getData(tumorales,x+dx[i]*xStep,y+dy[i]*yStep);
  if(tumorales < 10000000)
   {
   possibles.push_back(i);
   }
  }
 }
 
// Propagation de l'exces des tumorales sur les possibles 
int nbPoss=possibles.size();
if(nbPoss)
 {
 double moyenne=exces/nbPoss;
 int dec=(int)(nbPoss*fGNA->getRandom());
 for(int j=0;j<nbPoss-1;j++)
  {
  int i=possibles[(j+dec)%nbPoss];
  nbTumorales.getData(tumorales,x+dx[i]*xStep,y+dy[i]*yStep);
  nbSaines.getData(saines,x+dx[i]*xStep,y+dy[i]*yStep);
  int conv=fGNA->getPoisson(moyenne);
  if(conv > exces)
   {
   conv=exces;
   }
  if(conv+tumorales > 10000000)
   {
   conv=10000000-tumorales;
   }
  if(conv > saines)
   {
   conv=saines;
   }
  tumorales+=conv;
  saines-=conv;
  exces-=conv;
  nbTumorales.setData(tumorales,x+dx[i]*xStep,y+dy[i]*yStep);
  nbSaines.setData(saines,x+dx[i]*xStep,y+dy[i]*yStep);
  }
 if(exces)
  {
  int i=possibles[(nbPoss-1+dec)%nbPoss];
  nbTumorales.getData(tumorales,x+dx[i]*xStep,y+dy[i]*yStep);
  nbSaines.getData(saines,x+dx[i]*xStep,y+dy[i]*yStep);
  if(exces+tumorales > 10000000)
   {
   exces=10000000-tumorales;
   }
  if(exces > saines)
   {
   exces=saines;
   }
  tumorales+=exces;
  saines-=exces;
  nbTumorales.setData(tumorales,x+dx[i]*xStep,y+dy[i]*yStep);
  nbSaines.setData(saines,x+dx[i]*xStep,y+dy[i]*yStep);
  }
 }
}				 
	
