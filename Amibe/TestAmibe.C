//
// Test General des classes de base
//

#include <iostream>

// Classes generales de l'automate
#include "EtatAutomate.h"
#include "EtatRouteur.h"
#include "Automate.h"
#include "RouteurSimple.h"
#include "RouteurBoucle.h"
#include "RouteurBoucleData.h"
#include "Jeton.h"
#include "Strategie.h"
#include "GenerateurNombresAleatoires.h"
#include "UtilitairesString.h"

// Classes derivees relatives au Amibe
#include "EtatAmibeImagerie.h"
#include "EtatAmibeIrradiation.h"
#include "FabriqueAmibeIrradiation.h"
#include "AmibeIrradiation.h"
#include "EtatAmibeBiologie.h"
#include "EtatAmibeTraducteur.h"
#include "EtatAmibePhysiqueMedicale.h"
#include "EtatAmibeMedical.h"
#include "AmibeStatus.h"

// Classes de visiteurs

#include <iostream>
#include <fstream>

using namespace std;

//__________________________________________________________________________________
Automate *buildTraitementNoPause(int nbFrac, double doseParFrac, 
                                 string irradStrat, string fichierFaisceau="")
{
// Automate traitement sns pause
//-------------------------------------------------------
// Definition des etats
//-------------------------------------------------------
//--> Etat initial
EtatAmibeImagerie *etatInit=new EtatAmibeImagerie();
etatInit->setNom("ImagerieAmibe");
etatInit->setCommentaire("Etat Initial de l'automate: Imagerie");
etatInit->setNomStrategie("AmibeImagerie");

//--> Etat irradiation
EtatAmibeIrradiation *etatIrrad=new EtatAmibeIrradiation();
etatIrrad->setNom("IrradAmibe");
etatIrrad->setCommentaire("Etat Irradiation de l'automate");
etatIrrad->setNomStrategie(irradStrat);
string nomParam=irradStrat;
nomParam+="::doseParFrac";
etatIrrad->setValeurParametre(nomParam,doseParFrac);
if(fichierFaisceau.length())
 {
 FabriqueAmibeIrradiation *fab=
  (FabriqueAmibeIrradiation *)etatIrrad->getFabriqueStrategie();
 AmibeIrradiation *strat=(AmibeIrradiation *)fab->fabriqueStrategie(irradStrat);
 if(strat)
  {
  strat->setNomFichierFaisceaux(fichierFaisceau);
  strat->lireFichierFaisceaux(true);
  }
 }

//--> Etat traducteur
EtatAmibeTraducteur *etatTrad=new EtatAmibeTraducteur();
etatTrad->setNom("TraducteurAmibe");
etatTrad->setCommentaire("Etat Traducteur de l'automate");
etatTrad->setNomStrategie("CopierSainesOriginales");

//--> Etat degats irradiation Hadron
EtatAmibeBiologie *etatDegIrrad=new EtatAmibeBiologie();
etatDegIrrad->setNom("BioDegatsAmibe");
etatDegIrrad->setCommentaire("Etat Biologie de l'automate: degats d'irradiation");
if(irradStrat=="AmibeIrradiationX")
 {
 etatDegIrrad->setNomStrategie("AmibeDegatsIrradiationX");
 }
else
 {
 etatDegIrrad->setNomStrategie("AmibeDegatsIrradiationHadron");
 }

//--> Etat mutations irradiation
EtatAmibeBiologie *etatMutIrrad=new EtatAmibeBiologie();
etatMutIrrad->setNom("BioMutationsAmibe");
etatMutIrrad->setCommentaire("Etat Biologie de l'automate: mutations dues aux irradiation");
etatMutIrrad->setNomStrategie("AmibeMutationIrradiation");

//--> Etat Proliferation 
EtatAmibeBiologie *etatProli=new EtatAmibeBiologie();
etatProli->setNom("ProliferationAmibe");
etatProli->setCommentaire("Etat Biologie de l'automate: Proliferation");
etatProli->setNomStrategie("AmibeProliferation");

//--> Etat Medical
EtatAmibeMedical *etatStatus=new EtatAmibeMedical();
etatStatus->setNom("StatusAmibe");
etatStatus->setCommentaire("Etat medical de l'automate: etat medical du Amibe");
etatStatus->setNomStrategie("AmibeStatus");

//--> Etat Physique Medicale
EtatAmibePhysiqueMedicale *etatHDV=new EtatAmibePhysiqueMedicale();
etatHDV->setNom("HDVAmibe");
etatHDV->setCommentaire("Etat Physique medicale de l'automate: HDV du Amibe");
etatHDV->setNomStrategie("AmibeHDV");

//-------------------------------------------------------
// Definition des routeurs
//-------------------------------------------------------
//--> Routeur Imagerie -> Irradiation
RouteurSimple *rImToIr = new RouteurSimple();
rImToIr->setNom("ImagerieToIrradiation");
rImToIr->setCommentaire("Imagerie -> Irradiation");
rImToIr->setEtatSuivant(etatIrrad);

//--> Routeur Irradiation -> Traducteur
RouteurSimple *rIrToTrad = new RouteurSimple();
rIrToTrad->setNom("IrradiationToTrad");
rIrToTrad->setCommentaire("Irradiation -> Traduction");
rIrToTrad->setEtatSuivant(etatTrad);

//--> Routeur Traducteur -> Degats Irradiation
RouteurSimple *rTradToDegIr = new RouteurSimple();
rTradToDegIr->setNom("TradToDegIrrad");
rTradToDegIr->setCommentaire("Traduction -> Degats Irradiations");
rTradToDegIr->setEtatSuivant(etatDegIrrad);

//--> Routeur Degats Irradiation -> Mutations Irradiation
RouteurSimple *rDegIrToMutIr = new RouteurSimple();
rDegIrToMutIr->setNom("DegIrradToMutIrrad");
rDegIrToMutIr->setCommentaire("Degats Irradiations -> Mutations Irradiations");
rDegIrToMutIr->setEtatSuivant(etatMutIrrad);

//--> Routeur Mutations Irradiation -> Proliferation
RouteurSimple *rMutIrToProli = new RouteurSimple();
rMutIrToProli->setNom("MutIrradToProli");
rMutIrToProli->setCommentaire("Mutations Irradiations -> Proliferation");
rMutIrToProli->setEtatSuivant(etatProli);

//--> Routeur Proliferation -> Irradiation ou Sortie
RouteurBoucle *rProliToIrOrF = new RouteurBoucle();
rProliToIrOrF->setNom("ProliToIrradiationOrMedical");
rProliToIrOrF->setCommentaire("Proliferation -> Irradiation ou Medical");
rProliToIrOrF->setEtatBoucle(etatIrrad);
rProliToIrOrF->setEtatSortie(etatStatus);
rProliToIrOrF->setCompteurInitial(nbFrac);

//--> Routeur Degats Irradiation -> Mutations Irradiation
RouteurSimple *rMedToPhyMed = new RouteurSimple();
rMedToPhyMed->setNom("MedToPhysMed");
rMedToPhyMed->setCommentaire("Medical -> Physique Medicale");
rMedToPhyMed->setEtatSuivant(etatHDV);

//-------------------------------------------------------
// Association des etats et des routeurs
//-------------------------------------------------------
etatInit->setRouteur(rImToIr);
etatIrrad->setRouteur(rIrToTrad);
etatTrad->setRouteur(rTradToDegIr);
etatDegIrrad->setRouteur(rDegIrToMutIr);
etatMutIrrad->setRouteur(rMutIrToProli);
etatProli->setRouteur(rProliToIrOrF);
etatStatus->setRouteur(rMedToPhyMed);

//-------------------------------------------------------
// Definition du jeton
//-------------------------------------------------------
Jeton *jeton=new Jeton();
jeton->setNom("Jeton");
jeton->setCommentaire("Jeton \"patient\"");

//-------------------------------------------------------
// fabrication de l'automate
//-------------------------------------------------------
Automate *a=new Automate();

a->setEtatInitial(etatInit);
a->setJeton(jeton);
a->setNom("TraitementNoPause");
a->setCommentaire("Traitement sans pause");

cout << "Ajout des etats" << endl;
a->ajouteEtat(etatInit);
a->ajouteEtat(etatIrrad);
a->ajouteEtat(etatTrad);
a->ajouteEtat(etatDegIrrad);
a->ajouteEtat(etatMutIrrad);
a->ajouteEtat(etatProli);
a->ajouteEtat(etatStatus);
a->ajouteEtat(etatHDV);

//-------------------------------------------------------
// Ajout d'un visiteur
//-------------------------------------------------------
//SuiviCartographieAmibe *scw=new SuiviCartographieAmibe();
//etatInit->setVisiteur(scw);
//etatMutIrrad->setVisiteur(scw);
//etatCicat->setVisiteur(scw);

return a; 
}


#include "CartographieVecteur.h"

//__________________________________________________________________________________
void printJeton(Jeton *j,ostream &fout=cout)
{
//
// Affichage du jeton
//
  if(fout == cout)
   {
   fout << "------> Resultat final <--------------------------------- " << endl;
   fout << j->getCommentaire() << endl;
   }
  CartographieVecteur<int> nbSaines;
  CartographieVecteur<int> nbTumorales;
  CartographieVecteur<string> zones;
  CartographieVecteur<double> doseFraction;
  CartographieVecteur<double> doseTotale;
  CartographieVecteur<double> EBRalpha;
  bool hasDoseFraction=j->getData("doseFraction",doseFraction);
  bool hasDoseTotale=j->getData("doseTotale",doseTotale);
  bool hasEBR=j->getData("EBRalpha",EBRalpha);
  if(j->getData("nbSaines",nbSaines) 
     && j->getData("nbTumorales",nbTumorales)
     && j->getData("zones",zones))
   {
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
     int saines=0;
     int tumorales=0;
     string nomZone="inconnue";
     nbSaines.getData(saines,x,y);
     nbTumorales.getData(tumorales,x,y);
     zones.getData(nomZone,x,y);
     fout << x << " " << y << " " << saines << " " << tumorales << " " <<
     nomZone;
     if(hasDoseFraction)
      {
      double dosef=0;
      doseFraction.getData(dosef,x,y);
      fout << " " << dosef;
      }
     else
      {
      fout << " 0.";
      }
     if(hasDoseTotale)
      {
      double doset=0;
      doseTotale.getData(doset,x,y);
      fout << " " << doset;
      }
     else
      {
      fout << " 0.";
      }
     if(hasEBR)
      {
      double EBR=0;
      EBRalpha.getData(EBR,x,y);
      fout << " " << EBR;
      }
     else
      {
      fout << " 1.";
      }
     fout << endl;
     }
    }
   }
 if(fout == cout)
  fout << "---------------------------------------------------------" << endl;
}

//__________________________________________________________________________________
void analyseJeton(Jeton *j, ostream &fout=cout)
{
//
// Analyse du jeton
//
  AmibeStatus::Status st=AmibeStatus::kGoodShape;
  bool tumControl=false;
  int compOAR=0;
  int compSaines=0;
  double ageAmibe=-1.;
  j->getData("ageAmibe",ageAmibe);
  double doseTotale=-1;
  int nbf=-1;
  if(j->getData("etatAmibe",st))
   {
   j->getData("controleTumeur",tumControl);
   j->getData("complicationOAR",compOAR);
   j->getData("complicationSaines",compSaines);
   }
  j->getData("doseTraitement",doseTotale); 
  j->getData("nombreDeFractions",nbf); 
  fout << doseTotale << " " << nbf << " " << ageAmibe << " " << st << " " << tumControl << " " << compOAR << " " << compSaines << endl;
}

//__________________________________________________________________________________
Jeton *runAutomate(Automate *a,int numAmibe)
{
//
// Initialisation de l'automate et lancement du traitement
//
 Jeton *j=new Jeton();
 char nomJeton[16];
 sprintf(nomJeton,"Amibe%d",numAmibe);
 j->setNom(nomJeton);
 a->setJeton(j);
 static map<string,double> lstParamsInit;
 if(numAmibe <= 1) // On recupere les valeurs des parametres
  {
  lstParamsInit=a->getValeursParametres();
  }
 else // sinon on initialise les valeurs des parametres 
  {
  a->setValeursParametres(lstParamsInit);
  }
 a->process();
 //system("cat SuiviCartographie.txt >> SuiviCartographies.txt");
 return j;
}

//__________________________________________________________________________________
void printParametresAutomate(Automate *a)
{
//
// Affichage des parametres de l'automate
//
cout << "-------> Parametre de l'automate " << a->getNom() << endl;
map<string,double> lstParams=a->getValeursParametres();
map<string,double>::iterator itp;
for(itp=lstParams.begin();itp!=lstParams.end();itp++)
 {
 cout << itp->first << " = " << itp->second << endl;
 }
cout << "--------------------------------------------------" << endl;
}

//__________________________________________________________________________________
bool SetParametreAutomate(Automate *a,string s)
{
//
// fixer la valeur du parametre de l'automate
// le string contient une chaine du type "nomParametre=valeur"
//
map<string,double> lstParams=a->getValeursParametres();
map<string,double>::iterator itp;
vector<string> splitted=splitString(s,"=");
bool found=false;
string parName="inconnu";
for(itp=lstParams.begin();itp!=lstParams.end() && !found;itp++)
 {
 parName=itp->first;
 if(parName.find(splitted[0])!=string::npos)
  {
  found=true;
  a->setValeurParametre(parName,stod(splitted[1]));
  }
 }
if(found)
 {
 cout << "Parametre \"" << parName << "\" = " << splitted[1] << endl;
 }
else
 {
 cout << "Parametre \"" << splitted[0] << "\" inconnu pour cet automate" << endl;
 }
return found;
}

//__________________________________________________________________________________
Etat *GetEtatMutation(Automate *a)
{
//
// Recherche de l'etat qui contient le modele de mutation
//
Etat *e=a->getEtat("BioMutationsAmibe");
if(!e)
 {
 EtatAutomate *ea=(EtatAutomate *)a->getEtat("IrradAmibe");
 e=ea->getAutomate()->getEtat("BioMutationsAmibe");
 }
return e;
}

//__________________________________________________________________________________
void SetMutation(Automate *a,string typeMutation)
{
//
// On fixe le modele de mutation pour l'automate
//
// Recherche de l'etat correspondant a la mutation
Etat *e=GetEtatMutation(a);
if(e)
 {
 e->setNomStrategie(typeMutation);
 }
else
 {
 cout << "Etat de mutation introuvable" << endl;
 abort();
 }
}

//__________________________________________________________________________________
void SetImagerie(Automate *a,string typeImagerie)
{
//
// On fixe le modele de mutation pour l'automate
//
// Recherche de l'etat correspondant a la mutation
Etat *e=a->getEtat("ImagerieAmibe");
if(e)
 {
 e->setNomStrategie(typeImagerie);
 }
else
 {
 cout << "Etat de mutation introuvable" << endl;
 abort();
 }
}

//__________________________________________________________________________________
void AfficheManuel(void)
{
//
// Affiche le manuel en cas d'erreur
//
system("cat ManuelTestAmibe.txt");
}

#include "CartographieVecteur.h"

//__________________________________________________________________________________
int main(int argc, char **argv)
{
//
// Programme principal
//
/*
Syntaxe d'utilisation de TestAmibe:

  TestAmibe [cle1=valeur1 [cle2=valeur2 [...]]
  
-------------------------------------------------------------------------------
Cle	Valeurs Possibles		Commentaire
	[valeur par defaut]
===============================================================================
nbf	un nombre [30]			Nombre de fractions
-------------------------------------------------------------------------------
dpf	un nombre [2]			Dose par fraction
-------------------------------------------------------------------------------
nbAmibe	un nombre [1]			Nombre de Amibes a traiter
-------------------------------------------------------------------------------
irrad	AmibeIrradiationX		Irradiation avec des X
	AmibeIrradiationProton1I		Irradiation avec des protons
					avec 1 incidence
	AmibeIrradiationProton2I		Irradiation avec des protons
					avec 2 incidences
	[AmibeIrradiationCarbone]	Irradiation avec des carbones
-------------------------------------------------------------------------------
trait	[NoPause]			Traitement sans pause
	WithPause			Traitement avec pause
	Config:nomDeFichier.pmrtConf	Lecture du fichier de configuration
					"nomDeFichier.pmrtConf"
-------------------------------------------------------------------------------
mutIr	[AmibeMutationIrradiation]	Mutation utilisant la dose par fraction
	AmibeMutationIrradiation2	Mutation utilisant la dose totale
-------------------------------------------------------------------------------
nomPar					fixe la valeur du parametre "nomPar"
-------------------------------------------------------------------------------
					

Exemple 1: Traitement sans pause avec une irradiation de protons 
---------- en 1 incidence et 40 fractions de 0,95.
	   
	   TestAmibe irrad=AmibeIrradiationProton1I nbf=40 dpf=0.95


Exemple 2: Traitement avec pause avec une irradiation de carbones
---------- en 25 fractions de 2. Le parametre EBRplateau est fixe a 3,5.
	   
	   TestAmibe nbf=25 trait=WithPause EBRplateau=3.5
*/

//-----------------------------------------------------------------
// Valeurs par defaut
//-----------------------------------------------------------------
bool ok=false;
string typeIrrad="AmibeIrradiationCarbone";
string typeAutomate="NoPause";
string typeMutation="AmibeMutationIrradiation";
string typeImage="AmibeImagerie";
string fichierFaisceaux="";
double dpf=2.;
int nbf=30;
int nbAmibe=1;
vector<string> toTreat;

//Decodage des arguments sous la forme "cle=valeur"
for(int i=1;i<argc;i++)
 {
 string commande=argv[i];
 if(commande.find("dpf=")!=string::npos)
  {
  commande.replace(0,4,"");
  dpf=atof(commande.data());
  cout << "dpf set to " << dpf << endl;
  }
 else if(commande.find("nbf=")!=string::npos)
  {
  commande.replace(0,4,"");
  nbf=atoi(commande.data());
  cout << "nbf set to " << nbf << endl;
  }
 else if(commande.find("irrad=")!=string::npos)
  {
  commande.replace(0,6,"");
  typeIrrad=commande.data();
  cout << "irrad set to " << typeIrrad << endl;
  }
 else if(commande.find("trait=")!=string::npos)
  {
  commande.replace(0,6,"");
  typeAutomate=commande.data();
  cout << "automate set to " << typeAutomate << endl;
  }
 else if(commande.find("nbAmibe=")!=string::npos)
  {
  commande.replace(0,8,"");
  nbAmibe=atoi(commande.data());
  cout << "nbAmibe set to " << nbAmibe << endl;
  }
 else if(commande.find("image=")!=string::npos)
  {
  commande.replace(0,6,"");
  typeImage=commande;
  cout << "typeImage set to " << typeImage << endl;
  }
 else if(commande.find("mutIr=")!=string::npos)
  {
  commande.replace(0,6,"");
  typeMutation=commande;
  cout << "typeMutation set to " << typeMutation << endl;
  }
 else if(commande.find("faisceaux=")!=string::npos)
  {
  commande.replace(0,10,"");
  fichierFaisceaux=commande;
  cout << "fichierFaisceau set to " << fichierFaisceaux << endl;
  }
 else
  {
  cout << "Commande \"" << commande << "\" inconnue" << endl;
  toTreat.push_back(commande);
  }
 }

//-----------------------------------------------------------------
// Fabrication de l'automate
//-----------------------------------------------------------------
Automate *a=0;
bool saveConfig=true;
if(typeAutomate=="WithPause")
 {
 //a=buildTraitementWithPause(nbf,dpf,typeIrrad);
 }
else if(typeAutomate=="NoPause")
 {
 a=buildTraitementNoPause(nbf,dpf,typeIrrad,fichierFaisceaux);
 }
else
 {
 cout << "Automate \""<<typeAutomate<<"\" inconnu" << endl;
 AfficheManuel();
 return -1;
 }

//-----------------------------------------------------------------
// On fixe le modele de mutation pour l'automate
//-----------------------------------------------------------------
SetMutation(a,typeMutation);
//-----------------------------------------------------------------
// On fixe le modele d'imagerie pour l'automate
//-----------------------------------------------------------------
SetImagerie(a,typeImage);

//-----------------------------------------------------------------
// On effectue un premier traitement fictif pour recuperer
// la liste des parametres car les strategies des
// etats ne sont pas encore instanciees
//-----------------------------------------------------------------
cout << "Run initial de l'automate..." << endl;
Jeton *j=runAutomate(a,0);
cout << "Run initial effectue." << endl;

//-----------------------------------------------------------------
// On fixe les valeurs des parametres indiques dans la commande
//-----------------------------------------------------------------
vector<double> moreData;
for(int i=0;i<toTreat.size();i++)
 {
 cout << "Traitement de " << toTreat[i] << endl;
 bool found=SetParametreAutomate(a,toTreat[i]);
 if(!found)
  {
  AfficheManuel();
  printParametresAutomate(a);
  return -3;
  }
 vector<string> splitted=splitString(toTreat[i],"=");
 moreData.push_back(stod(splitted[1]));
 }

//-----------------------------------------------------------------
// On effectue la boucle de traitement sur tous les Amibes
//-----------------------------------------------------------------
vector<Jeton *> jetons;
//system("rm SuiviCartographies.txt");
for(int numAmibe=1;numAmibe<=nbAmibe;numAmibe++)
 {
 if(!(numAmibe%5))
  {
  cout << "Traitement de l'Amibe " << numAmibe << endl;
  }
 bool print=(numAmibe==nbAmibe);
 Jeton *j=runAutomate(a,numAmibe);
// system("cat SuiviCartographie.txt >> SuiviCartographies.txt");
 if(print)
  {
  ofstream fcart("AmibeCarto.txt");
  fcart << typeImage << endl;
  printJeton(j,fcart);
  fcart.close();
  printParametresAutomate(a);
  }
 jetons.push_back(j);
 }

//-----------------------------------------------------------------
// Analyse des jetons et affichage dans un fichier texte
//-----------------------------------------------------------------
string fName="AnalyseResults";
fName+=typeIrrad;
fName+=".txt";
ofstream fanal(fName.data());
vector<Jeton *>::iterator itj;
map<string,double> AmibeStatus;
AmibeStatus["Ok    "]=0;
AmibeStatus["Malade"]=0;
AmibeStatus["Mort  "]=0;
for(itj=jetons.begin();itj!=jetons.end();itj++)
 {
 for(int i=0;i<moreData.size();i++)
  {
  fanal << moreData[i] << " ";
  }
 analyseJeton(*itj,fanal);
 AmibeStatus::Status st=AmibeStatus::kGoodShape;
 if((*itj)->getData("etatAmibe",st))
  {
  switch(st)
   {
    case AmibeStatus::kGoodShape : AmibeStatus["Ok    "]++;
 				   break;
    case AmibeStatus::kSick :      AmibeStatus["Malade"]++;
 				   break;
    case AmibeStatus::kDead :      AmibeStatus["Mort  "]++;
 				   break;
    default: cout << " Inconnu ";
   }
  } 
 }

fanal.close();

//-----------------------------------------------------------------
// Affichage du resultat du traitement
//-----------------------------------------------------------------
map<string,double>::iterator its;
for(its=AmibeStatus.begin();its!=AmibeStatus.end();its++)
 {
 cout << its->first << " : " << its->second/nbAmibe*100. << " %" << endl;
 }

//-----------------------------------------------------------------
// On ecrit le fichier ".dot" de l'automate pour verifier visuellement
// l'automate
//-----------------------------------------------------------------
ofstream fout("AmibeAutomate.dot");
a->ecrireDotFile(fout);
fout.close();
 
//-----------------------------------------------------------------
// C'est fini! 
//-----------------------------------------------------------------
return 0;
}
