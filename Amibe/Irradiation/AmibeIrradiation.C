//
// Classe d'AmibeIrradiation
//

#include "AmibeIrradiation.h"
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

//________________________________________________________
AmibeIrradiation::AmibeIrradiation(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeIrradiation";
fCommentaire="AmibeIrradiation de base";
doseParFrac=2.;
nombreDeFrac=0;
fXCentre=0.;
fYCentre=0.;
fFaisceaux.clear();
fNomFichierFaisceaux="FichierFaisceau.txt";
}

//________________________________________________________
AmibeIrradiation::~AmibeIrradiation(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeIrradiation::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("zones",zones);
//
return ok;
}

//________________________________________________________
Jeton *AmibeIrradiation::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeIrradiation
// Cette methode va ajouter au jeton deux cartographies:
//   cartographie dose de la fraction
//   cartographie dose totale jusqu'a maintenant
//

j->getData("zones",zones);
double xMin=zones.getXMin();
double xMax=zones.getXMax();
int dimX=zones.getDimX();
double yMin=zones.getYMin();
double yMax=zones.getYMax();
int dimY=zones.getDimY();

bool ok=j->getData("doseFraction",doseFraction);
if(!(ok && (doseFraction.getDimX() == dimX && doseFraction.getDimX()==dimY))) 
 {
 //cout << "Init doseFraction" << endl;
 doseFraction.setDimX(dimX);
 doseFraction.setXMin(xMin);
 doseFraction.setXMax(xMax);
 doseFraction.setDimY(dimY);
 doseFraction.setYMin(yMin);
 doseFraction.setYMax(yMax);
 }
 
ok=j->getData("doseTotale",doseTotale);
if(!(ok && (doseTotale.getDimX() == dimX && doseTotale.getDimX()==dimY))) 
 {
 //cout << "Init doseTotale" << endl;
 doseTotale.setDimX(dimX);
 doseTotale.setXMin(xMin);
 doseTotale.setXMax(xMax);
 doseTotale.setDimY(dimY);
 doseTotale.setYMin(yMin);
 doseTotale.setYMax(yMax);
 }

if(!j->getData("nombreDeFractions",nombreDeFrac))
 {
 //cout << "Init nombre de fractions" << endl;
 nombreDeFrac=0;
 doseTraitement=0.;
 double xStep=(xMax-xMin)/dimX;
 double yStep=(yMax-yMin)/dimY;
 for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
  {
  for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
   {
   doseTotale.setData(doseTraitement,x,y);
   }
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
Jeton *AmibeIrradiation::genereDonnee(Jeton *j)
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
bool AmibeIrradiation::setValeurParametre(string nomParam,double valeur)
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

//________________________________________________________
bool AmibeIrradiation::getRfromXYThetaL(double &r,double x, double y,double r0,
                                        double theta, double largeur)
{
//
// Verifie que le point (x,y) est dans la zone d'irradiation
// et retourne la distance r a l'entree de l'amibe si c'est le cas
//
 r=0.;
 bool res=false;
 x-=fXCentre;
 y-=fYCentre;
 theta*=(acos((double)-1.)/(double)180.0);
 double l=x*cos(theta)+y*sin(theta);
 double h=-x*sin(theta)+y*cos(theta);
 if(abs(h)<=(largeur/2.))
  {
  res=true;
  r=r0-l;
  }
 return res;
}

//________________________________________________________
void AmibeIrradiation::lireFichierFaisceaux(bool print)
{
//
// Lecture du fichier des faisceaux
// pour chaque ligne est indique le poids, l'angle et la largeur du faisceau
//
fFaisceaux.clear();
ifstream fin(fNomFichierFaisceaux.data());
if(!fin.is_open())
 {
 cout << "Le fichier " << fNomFichierFaisceaux << " n'a pas pu etre ouvert." <<
 endl;
 abort();
 }
double poids,angle,largeur;
double sumPoids=0.;
while(!fin.eof())
 {
 fin >> poids >> angle >> largeur;
 if(!fin.eof())
  {
  sumPoids+=poids;
  this->addFaisceau(poids,angle,largeur);
  }
 }
fin.close();
// renormalisation des poids
if(sumPoids>0)
 {
 for(int i=0;i<fFaisceaux.size();i++)
  {
  tuple <double,double,double> tmp=fFaisceaux[i];
  poids=get<0>(tmp)/sumPoids;
  get<0>(tmp)=poids;
  fFaisceaux[i]=tmp;
  }
 }
else
 {
 fFaisceaux.clear();
 }
//Affichage
if(print)
 {
 cout << "---------------------------------------" << endl; 
 cout << "Lecture de " << fNomFichierFaisceaux << endl;
 cout << "Incidences faisceaux : " << endl;
  for(int i=0;i<fFaisceaux.size();i++)
   {
   tuple <double,double,double> tmp=fFaisceaux[i];
   cout << i+1 << " ->";
   cout << " " << get<0>(tmp);
   cout << " " << get<1>(tmp);
   cout << " " << get<2>(tmp);
   cout << endl;
   }
 cout << "---------------------------------------" << endl; 
 }
}
