//
// Classe d'AmibeImagerie
//

#include "AmibeImagerie.h"
#include "CartographieVecteur.h"
#include <iostream>
#include <fstream>

using namespace std;

//________________________________________________________
AmibeImagerie::AmibeImagerie(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeImagerie";
fCommentaire="AmibeImagerie de base";
}

//________________________________________________________
AmibeImagerie::~AmibeImagerie(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *AmibeImagerie::resoudre(Jeton *j)
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
  if(d<=81)
   {
   tumorales=10000000;
   nomZone="Tumeur";
   }
  else if(d<1600)
   {
   saines=10000000;
   nomZone="Saine";
   }
  d=(x-30)*(x-30)+(y-30)*(y-30);
  if(d<=100)
   {
   nomZone="OAR";
   }
  nbSaines.setData(saines,x,y);
  nbTumorales.setData(tumorales,x,y);
  zones.setData(nomZone,x,y);
  int tumo=0;
  int sa=0;
  string z="truc";
  nbSaines.getData(sa,x,y);
  nbTumorales.getData(tumo,x,y);
  zones.getData(z,x,y);
  }
 }
 
j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
j->setData("zones",zones);

return j;
}

//________________________________________________________
Jeton *AmibeImagerie::genereDonnee(Jeton *j)
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

