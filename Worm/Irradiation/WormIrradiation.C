//
// Classe d'WormIrradiation
//

#include "WormIrradiation.h"
#include <cmath>

using namespace std;

//________________________________________________________
WormIrradiation::WormIrradiation(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="WormIrradiation";
fCommentaire="WormIrradiation de base";
doseParFrac=2.;
nombreDeFrac=0;
doseTraitement=0.;
}

//________________________________________________________
WormIrradiation::~WormIrradiation(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool WormIrradiation::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("zones",zones);
//
return ok;
}

//________________________________________________________
Jeton *WormIrradiation::resoudre(Jeton *j)
{
//
// Methode de resolution de WormIrradiation
// Cette methode va ajouter au jeton deux cartographies:
//   cartographie dose de la fraction
//   cartographie dose totale jusqu'a maintenant
//

j->getData("zones",zones);
double xMin=zones.getXMin();
double xMax=zones.getXMax();
int dim=zones.getDimX();

bool ok=j->getData("doseFraction",doseFraction);
if(!(ok && (doseFraction.getDimX() == dim))) 
 {
 //cout << "Init doseFraction" << endl;
 doseFraction.setDimX(dim);
 doseFraction.setXMin(xMin);
 doseFraction.setXMax(xMax);
 }
 
ok=j->getData("doseTotale",doseTotale);
if(!(ok && (doseTotale.getDimX() == dim))) 
 {
 //cout << "Init doseTotale" << endl;
 doseTotale.setDimX(dim);
 doseTotale.setXMin(xMin);
 doseTotale.setXMax(xMax);
 }

if(!j->getData("nombreDeFractions",nombreDeFrac))
 {
 //cout << "Init nombre de fractions" << endl;
 nombreDeFrac=0;
 doseTraitement=0.;
 double xStep=(xMax-xMin)/dim;
 for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
  {
  doseTotale.setData(doseTraitement,x);
  }
 }

nombreDeFrac++;
doseTraitement+=doseParFrac;
j->setData("nombreDeFractions",nombreDeFrac);
j->setData("doseTraitement",doseTraitement);
j->setData("doseFraction",doseFraction);
j->setData("doseTotale",doseTotale);
return j;
}

//________________________________________________________
Jeton *WormIrradiation::genereDonnee(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=true;

j->setData("nombreDeFractions",nombreDeFrac);
j->setData("doseTraitement",doseTraitement);
j->setData("doseFraction",doseFraction);
j->setData("doseTotale",doseTotale);

return j;
}

//________________________________________________________
bool WormIrradiation::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=true;
if(nomParam=="doseParFrac")
 {
 doseParFrac=valeur;
 }
// else if(nomParam=="nombreDeFrac")
//  {
//  nombreDeFrac=(int)valeur;
//  }
// else if(nomParam=="doseTraitement")
//  {
//  doseTraitement=valeur;
//  }
else
 {
 res=false;
 }
return res;
}
