//
// Classe d'AmibeHDEB
//

#include "AmibeHDEB.h"
#include <iostream>
#include <fstream>

using namespace std;

//________________________________________________________
AmibeHDEB::AmibeHDEB(void): Strategie()
{
//
// Constructeur par defaut
//
fNom="AmibeHDEB";
fCommentaire="AmibeHDEB de base";
}

//________________________________________________________
AmibeHDEB::~AmibeHDEB(void)
{
//
// Destructeur
//
}

//________________________________________________________
bool AmibeHDEB::peutOperer(Jeton *j)
{
//
// Test si les donnees sont conformes
//

bool ok=j->getData("SFSaines",SFSaines);
if(ok)
 {
 ok=j->getData("SFTumorales",SFTumorales);
 if(ok)
  {
  ok=j->getData("zones",zones);
  if(ok)
   {
   ok=j->getData("probaNoMutation",probaNoMutation);
   }
  }
 }
//
return ok;
}

//________________________________________________________
Jeton *AmibeHDEB::resoudre(Jeton *j)
{
//
// Methode de resolution de AmibeHDEB
//

j->getData("SFSaines",SFSaines);
j->getData("SFTumorales",SFTumorales);
j->getData("probaNoMutation",probaNoMutation);
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

//Creation des HDEB
vHDMort.clear();
vHDMut.clear();
map<string,int>::iterator itz;
for(itz=nbZone.begin();itz!=nbZone.end();itz++)
 {
 vector<double> *HDV=new vector<double>();
 HDV->resize(110);
 vHDMort[itz->first]=HDV;
 if(itz->first != "Tumeur")
  {
  HDV=new vector<double>();
  HDV->resize(110);
  vHDMut[itz->first]=HDV;
  }
 }

//Remplissage des HDV
double critere=0.;
double pMUT=0;
double seuil=0.;
map<string,int> countsMort;
map<string,int> countsMut;
for(int i=0;i<110;i++)
 {
 countsMort.clear();
 countsMut.clear();
 seuil=i/100.;
 for(double x=xMin+xStep/2.;x<xMax;x+=xStep)
  {
  for(double y=yMin+yStep/2.;y<yMax;y+=yStep)
   {
   critere=0.;
   pMUT=0.;
   zones.getData(zone,x,y);
   if(zone!="Air")
    {
    // On commence par les morts cellulaires
    if(zone=="Tumeur")
     {
     SFTumorales.getData(critere,x,y);
     }
    else
     {
     SFSaines.getData(critere,x,y);
     probaNoMutation.getData(pMUT,x,y);
     if(pMUT > 0) pMUT=1.-pMUT;
     if(pMUT>seuil)
      {
      countsMut[zone]++;
      }
     }
    critere=1.-critere;
    if(critere>seuil)
     {
     countsMort[zone]++;
     }
    }
   }
  }
 for(itz=nbZone.begin();itz!=nbZone.end();itz++)
  {
  double perCent=countsMort[itz->first]*100./nbZone[itz->first];
  (*vHDMort[itz->first])[i]=perCent;
  if(itz->first != "Tumeur")
   {
   perCent=countsMut[itz->first]*100./nbZone[itz->first];
   (*vHDMut[itz->first])[i]=perCent;
   }
  }
 }

// impression des HDV dans un fichier ASCII
ofstream fout("AmibeHDEBs.txt");
fout << "# Seuil";
for(itz=nbZone.begin();itz!=nbZone.end();itz++)
 {
 fout << "|Mort_" << itz->first;
 if(itz->first != "Tumeur") fout << "|Mut_" << itz->first;
 }
fout << endl;
for(int i=0;i<110;i++)
 {
 fout << i/100.;
 for(itz=nbZone.begin();itz!=nbZone.end();itz++)
  {
  fout << " " << (*vHDMort[itz->first])[i];
  if(itz->first != "Tumeur") fout << " " << (*vHDMut[itz->first])[i];
  }
 fout << endl;
 }

fout.close();
return j;
}


//________________________________________________________
bool AmibeHDEB::setValeurParametre(string nomParam,double valeur)
{
//
// Ajuste la valeur du parametre en decodant la chaine de caracteres
//
bool res=false;
return res;
}
