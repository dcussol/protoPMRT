//
// Classe d'WormHDV
//

#include "WormHDV.h"
#include <iostream>
#include <fstream>

using namespace std;

//________________________________________________________
WormHDV::WormHDV(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="WormHDV";
fCommentaire="WormHDV de base";
}

//________________________________________________________
WormHDV::~WormHDV(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool WormHDV::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("doseTotale",doseTotale);
if(ok)
 {
 ok=j->getData("doseTraitement",doseTraitement);
 if(ok)
  {
  ok=j->getData("zones",zones);
  }
 }
//
return ok;
}

//________________________________________________________
Jeton *WormHDV::resoudre(Jeton *j)
{
//
// Methode de resolution de WormHDV
// Cette methode va modifier deux cartographies:
//

j->getData("doseTotale",doseTotale);
j->getData("doseTraitement",doseTraitement);
j->getData("zones",zones);

double xMin=zones.getXMin();
double xMax=zones.getXMax();
int dim=zones.getDimX();

double xStep=(xMax-xMin)/dim;

string zone="unknown";
// Comptage des zones
map<string,int> nbZone;
nbZone.clear();
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 zones.getData(zone,x);
 nbZone[zone]++;
 }

//Creation des HDV
vHDV.clear();
map<string,int>::iterator itz;
for(itz=nbZone.begin();itz!=nbZone.end();itz++)
 {
 vector<double> *HDV=new vector<double>();
 HDV->resize(110);
 vHDV[itz->first]=HDV;
 }

//Remplissage des HDV
double dose=0.;
double seuil=0.;
map<string,int> counts;
for(int i=0;i<110;i++)
 {
 counts.clear();
 seuil=doseTraitement*i/100.;
 for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
  {
  doseTotale.getData(dose,x);
  if(dose>seuil)
   {
   zones.getData(zone,x);
   counts[zone]++;
   }
  }
 for(itz=nbZone.begin();itz!=nbZone.end();itz++)
  {
  double perCent=counts[itz->first]*100./nbZone[itz->first];
  (*vHDV[itz->first])[i]=perCent;
  }
 }

// impression des HDV dans un fichier ASCII
ofstream fout("WormHDVs.txt");
fout << "# Seuil";
for(itz=nbZone.begin();itz!=nbZone.end();itz++)
 {
 fout << "|" << itz->first;
 }
fout << endl;
for(int i=0;i<110;i++)
 {
 fout << i/100.;
 for(itz=nbZone.begin();itz!=nbZone.end();itz++)
  {
  fout << " " << (*vHDV[itz->first])[i];
  }
 fout << endl;
 }

fout.close();
return j;
}


//________________________________________________________
bool WormHDV::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=false;
return res;
}
