//
// Classe d'WormImagerie
//

#include "WormImagerie.h"
#include "CartographieVecteur.h"

//________________________________________________________
WormImagerie::WormImagerie(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="WormImagerie";
fCommentaire="WormImagerie de base";
}

//________________________________________________________
WormImagerie::~WormImagerie(void)
{
//
// Destructeur
//
}

//________________________________________________________
Jeton *WormImagerie::resoudre(Jeton *j)
{
//
// Methode de resolution de WormImagerie
// Cette methode va ajouter au jeton trois cartographies:
//   cartographie du nombre de cellules saines
//   cartographie du nombre de cellules tumorales
//   cartographie de zones (Saine 1, Tumeur, Saine 2)
//

CartographieVecteur<int> nbSaines;
CartographieVecteur<int> nbTumorales;
CartographieVecteur<string> zones;

nbSaines.setDimX(50);
nbTumorales.setDimX(50);
zones.setDimX(50);
nbSaines.setXMin(0);
nbTumorales.setXMin(0);
zones.setXMin(0);
nbSaines.setXMax(100);
nbTumorales.setXMax(100);
zones.setXMax(100);

for(double x=1;x<100;x+=2)
 {
 int saines=10000000;
 int tumorales=0;
 string nomZone="Saine 1";
 if(x>= 46 && x <=54)
  {
  saines=0;
  tumorales=10000000;
  nomZone="Tumeur";
  }
 else if(x > 54)
  {
  nomZone="Saine 2";
  }
 nbSaines.setData(saines,x);
 nbTumorales.setData(tumorales,x);
 zones.setData(nomZone,x);
 }

j->setData("nbSaines",nbSaines);
j->setData("nbTumorales",nbTumorales);
j->setData("zones",zones);

return j;
}

//________________________________________________________
Jeton *WormImagerie::genereDonnee(Jeton *j)
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

