//
// Classe d'AmibeImagerie2
//

#include "AmibeImagerie2.h"
#include "CartographieVecteur.h"
#include <iostream>
#include <fstream>

using namespace std;

//________________________________________________________
AmibeImagerie2::AmibeImagerie2(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeImagerie2";
fCommentaire="AmibeImagerie2 de base";
}

//________________________________________________________
AmibeImagerie2::~AmibeImagerie2(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *AmibeImagerie2::resoudre(Jeton *j)
{
//
// Methode de resolution de WormImagerie
// Cette methode va ajouter au jeton trois cartographies:
//   cartographie du nombre de cellules saines
//   cartographie du nombre de cellules tumorales
//   cartographie de zones (Air, Saine, Tumeur, OAR)
//

CartographieVecteur<int> nbSaines;
CartographieVecteur<int> nbTumorales;
CartographieVecteur<string> zones;

nbSaines.setDimX(100);
nbTumorales.setDimX(100);
nbSaines.setDimY(100);
nbTumorales.setDimY(100);
zones.setDimX(100);
zones.setDimY(100);
nbSaines.setXMin(0);
nbTumorales.setXMin(0);
zones.setXMin(0);
nbSaines.setXMax(100);
nbTumorales.setXMax(100);
zones.setXMax(100);
nbSaines.setYMin(0);
nbTumorales.setYMin(0);
zones.setYMin(0);
nbSaines.setYMax(100);
nbTumorales.setYMax(100);
zones.setYMax(100);

int saines=10000000;
int tumorales=0;
string nomZone="Air";
double xMin=zones.getXMin();
double xMax=zones.getXMax();
int dimX=zones.getDimX();
double yMin=zones.getYMin();
double yMax=zones.getYMax();
int dimY=zones.getDimY();
double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  saines=0;
  tumorales=0;
  nomZone="Air";
  double d=(x-50)*(x-50)+(y-50)*(y-50);
  if(d<1600)
   {
   saines=10000000;
   tumorales=0;
   nomZone="Saine";
   }
  d=(x-30)*(x-30)+(y-30)*(y-30);
  if(d<=100)
   {
   saines=10000000;
   tumorales=0;
   nomZone="OAR1";
   }
  d=(x-50)*(x-50)+(y-80)*(y-80);
  if(d<=16)
   {
   saines=10000000;
   tumorales=0;
   nomZone="OAR2";
   }
  d=(x-65)*(x-65)+(y-40)*(y-40);
  if(d<=25)
   {
   saines=10000000;
   tumorales=0;
   nomZone="OAR3";
   }
  d=((x-50)*(x-50))/(9.*9.)+(y-50)*(y-50)/(4.*4.);
  if(d<=1.)
   {
   tumorales=10000000;
   saines=0;
   nomZone="Tumeur";
   }
  nbSaines.setData(saines,x,y);
  nbTumorales.setData(tumorales,x,y);
  zones.setData(nomZone,x,y);
  }
 }
 
j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
j->setData("zones",zones);

return j;
}

//________________________________________________________
Jeton *AmibeImagerie2::genereDonnee(Jeton *j)
{
//
// Test si les donnees sont conformes
//

//
// Travail de la donnee
//
CartographieVecteur<int> nbSaines;
CartographieVecteur<int> nbTumorales;
CartographieVecteur<string> zones;

bool ok=true;

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
j->setData("zones",zones);

return j;
}

