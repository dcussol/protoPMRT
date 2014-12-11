//
// Classe d'AmibeHDV
//

#include "AmibeHDV.h"
#include <iostream>
#include <fstream>

using namespace std;

//________________________________________________________
AmibeHDV::AmibeHDV(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeHDV";
fCommentaire="AmibeHDV de base";
}

//________________________________________________________
AmibeHDV::~AmibeHDV(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeHDV::peutOperer(Jeton *j)
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
Jeton *AmibeHDV::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeHDV
//

j->getData("doseTotale",doseTotale);
j->getData("doseTraitement",doseTraitement);
j->getData("zones",zones);

double xMin=zones.getXMin();
double xMax=zones.getXMax();
int dimX=zones.getDimX();
double yMin=zones.getYMin();
double yMax=zones.getYMax();
int dimY=zones.getDimY();

double xStep=(xMax-xMin)/dimX;
double yStep=(yMax-yMin)/dimY;

string zone="unknown";
// Comptage des zones
map<string,int> nbZone;
nbZone.clear();
for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
 {
 for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
  {
  zones.getData(zone,x,y);
  if(zone!="Air") nbZone[zone]++;
  }
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
  for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
   {
   doseTotale.getData(dose,x,y);
   if(dose>seuil)
    {
    zones.getData(zone,x,y);
    if(zone!="Air") counts[zone]++;
    }
   }
  }
 for(itz=nbZone.begin();itz!=nbZone.end();itz++)
  {
  double perCent=counts[itz->first]*100./nbZone[itz->first];
  (*vHDV[itz->first])[i]=perCent;
  }
 }

// impression des HDV dans un fichier ASCII
ofstream fout("AmibeHDVs.txt");
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
bool AmibeHDV::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=false;
return res;
}
