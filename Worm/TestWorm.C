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

// Classes derivees relatives au Worm
#include "EtatWormImagerie.h"
#include "EtatWormIrradiation.h"
#include "EtatWormBiologie.h"
#include "EtatWormMedical.h"
#include "EtatWormPhysiqueMedicale.h"
#include "EtatWormTraducteur.h"
#include "WormStatus.h"

// Classes de visiteurs
#include "VisiteurWorm.h"
#include "PrintWorm.h"
#include "SuiviCartographieWorm.h"

#include <iostream>
#include <fstream>

using namespace std;

//__________________________________________________________________________________
Automate *buildTraitementNoPause(int nbFrac, double doseParFrac, string irradStrat)
{
// Automate traitement sns pause
//-------------------------------------------------------
// Definition des etats
//-------------------------------------------------------
//--> Etat initial
EtatWormImagerie *etatInit=new EtatWormImagerie();
etatInit->setNom("ImagerieWorm");
etatInit->setCommentaire("Etat Initial de l'automate: Imagerie");
etatInit->setNomStrategie("WormImagerie");

//--> Etat irradiation
EtatWormIrradiation *etatIrrad=new EtatWormIrradiation();
etatIrrad->setNom("IrradWorm");
etatIrrad->setCommentaire("Etat Irradiation de l'automate");
etatIrrad->setNomStrategie(irradStrat);
string nomParam=irradStrat;
nomParam+="::doseParFrac";
etatIrrad->setValeurParametre(nomParam,doseParFrac);

//--> Etat traducteur
EtatWormTraducteur *etatTrad=new EtatWormTraducteur();
etatTrad->setNom("TraducteurWorm");
etatTrad->setCommentaire("Etat Traducteur de l'automate");
etatTrad->setNomStrategie("CopierSainesOriginales");

//--> Etat degats irradiation Hadron
EtatWormBiologie *etatDegIrrad=new EtatWormBiologie();
etatDegIrrad->setNom("BioDegatsWorm");
etatDegIrrad->setCommentaire("Etat Biologie de l'automate: degats d'irradiation");
if(irradStrat=="WormIrradiationX")
 {
 etatDegIrrad->setNomStrategie("WormDegatsIrradiationX");
 }
else
 {
 etatDegIrrad->setNomStrategie("WormDegatsIrradiationHadron");
 }

//--> Etat mutations irradiation
EtatWormBiologie *etatMutIrrad=new EtatWormBiologie();
etatMutIrrad->setNom("BioMutationsWorm");
etatMutIrrad->setCommentaire("Etat Biologie de l'automate: mutations dues aux irradiation");
etatMutIrrad->setNomStrategie("WormMutationIrradiation");

//--> Etat mutations irradiation
EtatWormBiologie *etatPropagTum=new EtatWormBiologie();
etatPropagTum->setNom("PropagationTumeurWorm");
etatPropagTum->
     setCommentaire("Etat Biologie de l'automate: Propagation de la tumeur");
etatPropagTum->setNomStrategie("WormPropagationTumeur");

//--> Etat Proliferation 
EtatWormBiologie *etatProli=new EtatWormBiologie();
etatProli->setNom("ProliferationWorm");
etatProli->setCommentaire("Etat Biologie de l'automate: Proliferation");
etatProli->setNomStrategie("WormProliferation");

//--> Etat Cicatrisation
EtatWormBiologie *etatCicat=new EtatWormBiologie();
etatCicat->setNom("CicatrisationWorm");
etatCicat->setCommentaire("Etat Biologie de l'automate: Cicatrisation");
etatCicat->setNomStrategie("WormCicatrisation");

//--> Etat Medical
EtatWormMedical *etatStatus=new EtatWormMedical();
etatStatus->setNom("StatusWorm");
etatStatus->setCommentaire("Etat medical de l'automate: etat medical du Worm");
etatStatus->setNomStrategie("WormStatus");

//--> Etat Physique Medicale
EtatWormPhysiqueMedicale *etatHDV=new EtatWormPhysiqueMedicale();
etatHDV->setNom("HDVWorm");
etatHDV->setCommentaire("Etat Physique medicale de l'automate: HDV du Worm");
etatHDV->setNomStrategie("WormHDV");

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

//--> Routeur Mutations Irradiation -> Propagation Tumeur
RouteurSimple *rMutIrToPropTum = new RouteurSimple();
rMutIrToPropTum->setNom("MutIrradToPropTum");
rMutIrToPropTum->setCommentaire("Mutations Irradiations -> Proliferation");
rMutIrToPropTum->setEtatSuivant(etatPropagTum);

//--> Routeur Propagation Tumeur -> Proliferation
RouteurSimple *rPropTumToProli = new RouteurSimple();
rPropTumToProli->setNom("PropTumToProli");
rPropTumToProli->setCommentaire("Mutations Irradiations -> Proliferation");
rPropTumToProli->setEtatSuivant(etatProli);

//--> Routeur Propagation Tumeur -> Proliferation
RouteurSimple *rProliToCicat = new RouteurSimple();
rProliToCicat->setNom("ProliToCicat");
rProliToCicat->setCommentaire("Proliferation -> Cicatrisation");
rProliToCicat->setEtatSuivant(etatCicat);

//--> Routeur Proliferation -> Irradiation ou Sortie
RouteurBoucle *rCicatToIrOrF = new RouteurBoucle();
rCicatToIrOrF->setNom("CicatToIrradiationOrMedical");
rCicatToIrOrF->setCommentaire("Cicatrisation -> Irradiation ou Medical");
rCicatToIrOrF->setEtatBoucle(etatIrrad);
rCicatToIrOrF->setEtatSortie(etatStatus);
rCicatToIrOrF->setCompteurInitial(nbFrac);

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
etatMutIrrad->setRouteur(rMutIrToPropTum);
etatPropagTum->setRouteur(rPropTumToProli);
etatProli->setRouteur(rProliToCicat);
etatCicat->setRouteur(rCicatToIrOrF);
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
a->ajouteEtat(etatPropagTum);
a->ajouteEtat(etatProli);
a->ajouteEtat(etatCicat);
a->ajouteEtat(etatStatus);
a->ajouteEtat(etatHDV);

//-------------------------------------------------------
// Ajout d'un visiteur
//-------------------------------------------------------
//SuiviCartographieWorm *scw=new SuiviCartographieWorm();
//etatInit->setVisiteur(scw);
//etatMutIrrad->setVisiteur(scw);
//etatCicat->setVisiteur(scw);

return a; 
}

//__________________________________________________________________________________
Automate *buildAutomateIrradiation(double doseParFrac, string irradStrat)
{
// Automate Irradiation pour l'Etat Automate IrradWorm
//-------------------------------------------------------
// Definition des etats
//-------------------------------------------------------
//--> Etat irradiation
EtatWormIrradiation *etatIrrad=new EtatWormIrradiation();
etatIrrad->setNom("IrradWorm");
etatIrrad->setCommentaire("Etat Irradiation de l'automate");
etatIrrad->setNomStrategie(irradStrat);
string nomParam=irradStrat;
nomParam+="::doseParFrac";
etatIrrad->setValeurParametre(nomParam,doseParFrac);

//--> Etat traducteur
EtatWormTraducteur *etatTrad=new EtatWormTraducteur();
etatTrad->setNom("TraducteurWorm");
etatTrad->setCommentaire("Etat Traducteur de l'automate");
etatTrad->setNomStrategie("CopierSainesOriginales");

//--> Etat degats irradiation Hadron
EtatWormBiologie *etatDegIrrad=new EtatWormBiologie();
etatDegIrrad->setNom("BioDegatsWorm");
etatDegIrrad->setCommentaire("Etat Biologie de l'automate: degats d'irradiation");
if(irradStrat=="WormIrradiationX")
 {
 etatDegIrrad->setNomStrategie("WormDegatsIrradiationX");
 }
else
 {
 etatDegIrrad->setNomStrategie("WormDegatsIrradiationHadron");
 }

//--> Etat mutations irradiation
EtatWormBiologie *etatMutIrrad=new EtatWormBiologie();
etatMutIrrad->setNom("BioMutationsWorm");
etatMutIrrad->setCommentaire("Etat Biologie de l'automate: mutations dues aux irradiation");
etatMutIrrad->setNomStrategie("WormMutationIrradiation");

//-------------------------------------------------------
// Definition des routeurs
//-------------------------------------------------------
//--> Routeur Irrad -> Traducteur
RouteurSimple *rIrToTrad = new RouteurSimple();
rIrToTrad->setNom("IrradToTraduction");
rIrToTrad->setCommentaire("Irradiations -> Traducteur");
rIrToTrad->setEtatSuivant(etatTrad);

//--> Routeur Traducteur -> Degtas d'irradiation
RouteurSimple *rTradToDegIr = new RouteurSimple();
rTradToDegIr->setNom("TraductionToDegats");
rTradToDegIr->setCommentaire("Traduction -> Degats");
rTradToDegIr->setEtatSuivant(etatDegIrrad);

//--> Routeur Degats Irradiation -> Mutations Irradiation
RouteurSimple *rDegIrToMutIr = new RouteurSimple();
rDegIrToMutIr->setNom("DegIrradToMutIrrad");
rDegIrToMutIr->setCommentaire("Degats Irradiations -> Mutations Irradiations");
rDegIrToMutIr->setEtatSuivant(etatMutIrrad);

//-------------------------------------------------------
// Association des etats et des routeurs
//-------------------------------------------------------
etatIrrad->setRouteur(rIrToTrad);
etatTrad->setRouteur(rTradToDegIr);
etatDegIrrad->setRouteur(rDegIrToMutIr);

//-------------------------------------------------------
// fabrication de l'automate
//-------------------------------------------------------
Automate *a=new Automate();

a->setNom("IrradiationWorm");
a->setCommentaire("Automate de l'irradiation du Worm");
a->setEtatInitial(etatIrrad);

cout << "Ajout des etats" << endl;
a->ajouteEtat(etatIrrad);
a->ajouteEtat(etatTrad);
a->ajouteEtat(etatDegIrrad);
a->ajouteEtat(etatMutIrrad);

return a; 
}

//__________________________________________________________________________________
Automate *buildAutomateRepos(void)
{
// Automate pour l'EtatAutomate ReposWorm
//-------------------------------------------------------
// Definition des etats
//-------------------------------------------------------
//--> Etat Propagation de la tumeur
EtatWormBiologie *etatPropagTum=new EtatWormBiologie();
etatPropagTum->setNom("PropagationTumeurWorm");
etatPropagTum->
     setCommentaire("Etat Biologie de l'automate: Propagation de la tumeur");
etatPropagTum->setNomStrategie("WormPropagationTumeur");

//--> Etat Proliferation 
EtatWormBiologie *etatProli=new EtatWormBiologie();
etatProli->setNom("ProliferationWorm");
etatProli->setCommentaire("Etat Biologie de l'automate: Proliferation");
etatProli->setNomStrategie("WormProliferation");

//--> Etat Cicatrisation
EtatWormBiologie *etatCicat=new EtatWormBiologie();
etatCicat->setNom("CicatrisationWorm");
etatCicat->setCommentaire("Etat Biologie de l'automate: Cicatrisation");
etatCicat->setNomStrategie("WormCicatrisation");

//-------------------------------------------------------
// Definition des routeurs
//-------------------------------------------------------
//--> Routeur Propagation Tumeur -> Proliferation
RouteurSimple *rPropTumToProli = new RouteurSimple();
rPropTumToProli->setNom("PropTumToProli");
rPropTumToProli->setCommentaire("Mutations Irradiations -> Proliferation");
rPropTumToProli->setEtatSuivant(etatProli);

//--> Routeur Propagation Tumeur -> Proliferation
RouteurSimple *rProliToCicat = new RouteurSimple();
rProliToCicat->setNom("ProliToCicat");
rProliToCicat->setCommentaire("Proliferation -> Cicatrisation");
rProliToCicat->setEtatSuivant(etatCicat);

//-------------------------------------------------------
// Association des etats et des routeurs
//-------------------------------------------------------
etatPropagTum->setRouteur(rPropTumToProli);
etatProli->setRouteur(rProliToCicat);

//-------------------------------------------------------
// fabrication de l'automate
//-------------------------------------------------------
Automate *a=new Automate();

a->setNom("ReposWorm");
a->setCommentaire("Repos du Worm");
a->setEtatInitial(etatPropagTum);

cout << "Ajout des etats" << endl;
a->ajouteEtat(etatPropagTum);
a->ajouteEtat(etatProli);
a->ajouteEtat(etatCicat);

return a; 
}

//__________________________________________________________________________________
Automate *buildAutomatePause(void)
{
// Automate pour l'EtatAutomate PauseWorm
// On se base sur l'automate ReposWorm sur lequel on va attribuer
// un RouteurBoucle a l'etat CicatrisationWorm.
Automate *a=buildAutomateRepos();
a->setNom("AutomatePause");

Etat *etatCicat=a->getEtat("CicatrisationWorm");
Etat *etatPropagTum=a->getEtat("PropagationTumeurWorm");

//--> Routeur Cicat -> Propag Tumeur ou Sortie
RouteurBoucle *rCicToPropOrOut= new RouteurBoucle();
rCicToPropOrOut->setNom("CicatToPropagTumOrOut");
rCicToPropOrOut->setCommentaire("Cicatrisation -> Propagation Tumeur ou Sortie");
rCicToPropOrOut->setEtatBoucle(etatPropagTum);
rCicToPropOrOut->setCompteurInitial(2);


//-------------------------------------------------------
// Association des etats et des routeurs
//-------------------------------------------------------
cout << "Etat Cicat: Routeur = " << etatCicat->getRouteur() << endl;
if(etatCicat->getRouteur())
 {
 delete etatCicat->getRouteur();
 }
etatCicat->setRouteur(rCicToPropOrOut);
return a;
}

//__________________________________________________________________________________
Automate *buildTraitementWithPause(int nbFrac, double doseParFrac, string irradStrat)
{
// Automate Traitement avec pause
//-------------------------------------------------------
// Definition des etats
//-------------------------------------------------------
//--> Etat initial
EtatWormImagerie *etatInit=new EtatWormImagerie();
etatInit->setNom("ImagerieWorm");
etatInit->setCommentaire("Etat Initial de l'automate: Imagerie");
etatInit->setNomStrategie("WormImagerie");

//--> Etat irradiation
EtatAutomate *etatIrrad=new EtatAutomate();
etatIrrad->setNom("IrradWorm");
etatIrrad->setCommentaire("Etat Irradiation de l'automate");
Automate *aIrrad=buildAutomateIrradiation(doseParFrac,irradStrat);
etatIrrad->setAutomate(aIrrad);
etatIrrad->setEtatInitial(aIrrad->getEtat("IrradWorm"));

//--> Etat Repos Apres Irradiation
EtatAutomate *etatRepos=new EtatAutomate();
etatRepos->setNom("ReposWorm");
etatRepos->setCommentaire("Etat repos du Worm apres irradiation");
Automate *aRepos=buildAutomateRepos();
etatRepos->setAutomate(aRepos);
etatRepos->setEtatInitial(aRepos->getEtat("PropagationTumeurWorm"));

//--> Etat Routeur pour la boucle s'il est atteint
EtatRouteur *etatRouteur=new EtatRouteur();
etatRouteur->setNom("EtatRouteur");
etatRouteur->setCommentaire("Etat intermediaire permettant de tester plusieurs conditions");

//--> Etat Pause
EtatAutomate *etatPause=new EtatAutomate();
etatPause->setNom("PauseWorm");
etatPause->setCommentaire("Etat pause");
Automate *aPause=buildAutomatePause();
aPause->setNom("PauseWorm");
etatPause->setAutomate(aPause);
etatPause->setEtatInitial(aPause->getEtat("PropagationTumeurWorm"));

//--> Etat Medical
EtatWormMedical *etatStatus=new EtatWormMedical();
etatStatus->setNom("StatusWorm");
etatStatus->setCommentaire("Etat medical de l'automate: etat medical du Worm");
etatStatus->setNomStrategie("WormStatus");

//--> Etat Physique Medicale
EtatWormPhysiqueMedicale *etatHDV=new EtatWormPhysiqueMedicale();
etatHDV->setNom("HDVWorm");
etatHDV->setCommentaire("Etat Physique medicale de l'automate: HDV du Worm");
etatHDV->setNomStrategie("WormHDV");

//-------------------------------------------------------
// Definition des routeurs
//-------------------------------------------------------
//--> Routeur Imagerie -> Irradiation
RouteurSimple *rImToIr = new RouteurSimple();
rImToIr->setNom("ImagerieToIrradiation");
rImToIr->setCommentaire("Imagerie -> Irradiation");
rImToIr->setEtatSuivant(etatIrrad);

//--> Routeur Irradiation -> Repos
RouteurSimple *rIrToRepos = new RouteurSimple();
rIrToRepos->setNom("IrradToRepos");
rIrToRepos->setCommentaire("Irradiation -> Repos");
rIrToRepos->setEtatSuivant(etatRepos);

//--> Routeur Repos -> Irradiation ou Pause
RouteurBoucle *rRoutToIrOrPause = new RouteurBoucle();
rRoutToIrOrPause->setNom("RouteurToIrradiationOrPause");
rRoutToIrOrPause->setCommentaire("Repos -> Irradiation ou Pause");
rRoutToIrOrPause->setEtatBoucle(etatIrrad);
rRoutToIrOrPause->setEtatSortie(etatPause);
rRoutToIrOrPause->setCompteurInitial(5);

//--> Routeur Pause -> Irradiation
RouteurSimple *rPauseToIr = new RouteurSimple();
rPauseToIr->setNom("PauseToIrradiation");
rPauseToIr->setCommentaire("Pause -> Irradiation");
rPauseToIr->setEtatSuivant(etatIrrad);

//--> Routeur Repos -> Routeur ou Medical
RouteurBoucleData *rReposToRoutOrF = new RouteurBoucleData();
rReposToRoutOrF->setNom("ReposToRouteurOrMedical");
rReposToRoutOrF->setCommentaire("Repos -> Routeur ou Medical");
rReposToRoutOrF->setEtatBoucle(etatRouteur);
rReposToRoutOrF->setEtatSortie(etatStatus);
rReposToRoutOrF->setNomData("nombreDeFractions");
rReposToRoutOrF->setCompteurInitial(nbFrac);

//--> Routeur Degats Irradiation -> Mutations Irradiation
RouteurSimple *rMedToPhyMed = new RouteurSimple();
rMedToPhyMed->setNom("MedToPhysMed");
rMedToPhyMed->setCommentaire("Medical -> Physique Medicale");
rMedToPhyMed->setEtatSuivant(etatHDV);

//-------------------------------------------------------
// Association des etats et des routeurs
//-------------------------------------------------------
etatInit->setRouteur(rImToIr);
etatIrrad->setRouteur(rIrToRepos);
etatRepos->setRouteur(rReposToRoutOrF);
etatRouteur->setRouteur(rRoutToIrOrPause);
etatPause->setRouteur(rPauseToIr);
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
a->setNom("TraitementWithPause");
a->setCommentaire("Traitement avec pause");

cout << "Ajout des etats" << endl;
a->ajouteEtat(etatInit);
a->ajouteEtat(etatIrrad);
a->ajouteEtat(etatRepos);
a->ajouteEtat(etatPause);
a->ajouteEtat(etatStatus);
a->ajouteEtat(etatRouteur);
a->ajouteEtat(etatHDV);

//-------------------------------------------------------
// Ajout d'un visiteur
//-------------------------------------------------------
//SuiviCartographieWorm *scw=new SuiviCartographieWorm();
//etatInit->setVisiteur(scw);
//etatIrrad->setVisiteur(scw);
//etatPause->setVisiteur(scw);
//etatRepos->setVisiteur(scw);

return a; 
}

#include "CartographieVecteur.h"

//__________________________________________________________________________________
void printJeton(Jeton *j)
{
//
// Affichage du jeton
//
  cout << "------> Resultat final <--------------------------------- " << endl;
  cout << j->getCommentaire() << endl;
  CartographieVecteur<int> nbSaines;
  CartographieVecteur<int> nbTumorales;
  CartographieVecteur<string> zones;
  CartographieVecteur<double> doseFraction;
  CartographieVecteur<double> doseTotale;
  CartographieVecteur<double> doseTotaleMut;
  CartographieVecteur<double> EBRalpha;
  CartographieVecteur<double> SFsaines;
  CartographieVecteur<double> SFtumorales;
  CartographieVecteur<double> probMutation;
  if(j->getData("nbSaines",nbSaines) 
     && j->getData("nbTumorales",nbTumorales)
     && j->getData("zones",zones))
   {
   bool hasDoseFrac=j->getData("doseFraction",doseFraction);
   bool hasDoseTotale=j->getData("doseTotale",doseTotale);
   bool hasDoseTotaleMut=j->getData("doseTotaleMut",doseTotaleMut);
   bool hasEBR=j->getData("EBRalpha",EBRalpha);
   int s=-1;
   int t=-1;
   string z="unknown";
   double doseF=0.;
   double doseT=0.;
   double doseTM=0.;
   double EBR=0.;
   double sfS=-1.;
   double sfT=-1;
   double pMut=-1.;
   for(double x=1;x<100;x+=2)
    {
    s=-1;
    t=-1;
    z="unknown";
    doseF=0.;
    doseT=0.;
    doseTM=0.;
    EBR=0.;
    sfS=-1.;
    sfT=-1;
    pMut=-1.;
    nbSaines.getData(s,x);
    nbTumorales.getData(t,x);
    zones.getData(z,x);
    cout << x << " : " << s << " / " << t << " / " << z;
    if(hasDoseFrac && hasDoseTotale)
     {
     doseFraction.getData(doseF,x);
     doseTotale.getData(doseT,x);
     cout << " / " << doseF << " / " << doseT;
     }
    if(hasDoseTotaleMut)
     {
     doseTotaleMut.getData(doseTM,x);
     cout << " / " << doseTM;
     }
    if(hasEBR)
     {
     EBRalpha.getData(EBR,x);
     cout << " / " << EBR;
     }
    if(j->getData("SFSaines",SFsaines))
     {  
     SFsaines.getData(sfS,x);
     cout << " / " << sfS;
     }
    if(j->getData("SFTumorales",SFtumorales))
     {
     SFtumorales.getData(sfT,x);
     cout << " / " << sfT;
     }
    if(j->getData("probMutation",probMutation))
     {
     probMutation.getData(pMut,x);
     cout << " / " << pMut;
     }
    cout << endl;
    }
   }
  WormStatus::Status st=WormStatus::kGoodShape;
  cout << "Traitement effectue:" << endl;
  double ageWorm=0;
  double dpf=0.;
  int nbf=0.;
  j->getData("nombreDeFractions",nbf);
  j->getData("doseTraitement",dpf);
  cout << "Nombre de Fraction      : " << nbf << endl;
  cout << "Dose totale a la tumeur : " << dpf << endl;
  if(j->getData("ageWorm",ageWorm))
   {
   cout << "Age du Worm             : " << ageWorm << endl;
   }
  
  if(j->getData("etatWorm",st))
   {
   bool tumControl=false;
   j->getData("controleTumeur",tumControl);
   int compGradeSaine1=0;
   int compGradeSaine2=0;
   j->getData("complicationSaine1",compGradeSaine1);
   j->getData("complicationSaine2",compGradeSaine2);
   cout << "Etat du Worm         : ";
   switch(st)
    {
     case WormStatus::kGoodShape : cout << "Ok ";
                                    break;
     case WormStatus::kSick : cout << "Malade ";
                                    break;
     case WormStatus::kDead : cout << "Mort ";
                                    break;
     default: cout << " Inconnu ";
    } 
   cout << endl;
   cout << "Tumeur controlee     : ";
   if(tumControl) cout << "Oui"; else cout << "Non"; cout  << endl;
   cout << "Complications zone 1 : " << compGradeSaine1 << endl;
   cout << "Complications zone 2 : " << compGradeSaine2 << endl;
   }
 cout << "---------------------------------------------------------" << endl;
}

//__________________________________________________________________________________
void analyseJeton(Jeton *j, ostream &fout=cout)
{
//
// Analyse du jeton
//
  WormStatus::Status st=WormStatus::kGoodShape;
  bool tumControl=false;
  int compGradeSaine1=0;
  int compGradeSaine2=0;
  double ageWorm=-1.;
  j->getData("ageWorm",ageWorm);
  double doseTotale=-1;
  int nbf=-1;
  if(j->getData("etatWorm",st))
   {
   j->getData("controleTumeur",tumControl);
   j->getData("complicationSaine1",compGradeSaine1);
   j->getData("complicationSaine2",compGradeSaine2);
   }
  j->getData("doseTraitement",doseTotale); 
  j->getData("nombreDeFractions",nbf); 
  fout << doseTotale << " " << nbf << " " << ageWorm << " " << st << " " <<  tumControl << " " << compGradeSaine1 << " " << compGradeSaine2 << endl;
}

//__________________________________________________________________________________
Jeton *runAutomate(Automate *a,int numWorm)
{
//
// Initialisation de l'automate et lancement du traitement
//
 Jeton *j=new Jeton();
 char nomJeton[16];
 sprintf(nomJeton,"Worm%d",numWorm);
 j->setNom(nomJeton);
 a->setJeton(j);
 static map<string,double> lstParamsInit;
 if(numWorm <= 1) // On recupere les valeurs des parametres
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
Etat *e=a->getEtat("BioMutationsWorm");
if(!e)
 {
 EtatAutomate *ea=(EtatAutomate *)a->getEtat("IrradWorm");
 e=ea->getAutomate()->getEtat("BioMutationsWorm");
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
void AfficheManuel(void)
{
//
// Affiche le manuel en cas d'erreur
//
system("cat ManuelTestWorm.txt");
}

#include "CartographieVecteur.h"

//__________________________________________________________________________________
int main(int argc, char **argv)
{
//
// Programme principal
//
/*
Syntaxe d'utilisation de TestWorm:

  TestWorm [cle1=valeur1 [cle2=valeur2 [...]]
  
-------------------------------------------------------------------------------
Cle	Valeurs Possibles		Commentaire
	[valeur par defaut]
===============================================================================
nbf	un nombre [30]			Nombre de fractions
-------------------------------------------------------------------------------
dpf	un nombre [2]			Dose par fraction
-------------------------------------------------------------------------------
nbWorm	un nombre [1]			Nombre de worms a traiter
-------------------------------------------------------------------------------
irrad	WormIrradiationX		Irradiation avec des X
	WormIrradiationProton1I		Irradiation avec des protons
					avec 1 incidence
	WormIrradiationProton2I		Irradiation avec des protons
					avec 2 incidences
	[WormIrradiationCarbone]	Irradiation avec des carbones
-------------------------------------------------------------------------------
trait	[NoPause]			Traitement sans pause
	WithPause			Traitement avec pause
	Config:nomDeFichier.pmrtConf	Lecture du fichier de configuration
					"nomDeFichier.pmrtConf"
-------------------------------------------------------------------------------
mutIr	[WormMutationIrradiation]	Mutation utilisant la dose par fraction
	WormMutationIrradiation2	Mutation utilisant la dose totale
-------------------------------------------------------------------------------
nomPar					fixe la valeur du parametre "nomPar"
-------------------------------------------------------------------------------
					

Exemple 1: Traitement sans pause avec une irradiation de protons 
---------- en 1 incidence et 40 fractions de 0,95.
	   
	   TestWorm irrad=WormIrradiationProton1I nbf=40 dpf=0.95


Exemple 2: Traitement avec pause avec une irradiation de carbones
---------- en 25 fractions de 2. Le parametre EBRplateau est fixe a 3,5.
	   
	   TestWorm nbf=25 trait=WithPause EBRplateau=3.5
*/

//-----------------------------------------------------------------
// Valeurs par defaut
//-----------------------------------------------------------------
bool ok=false;
string typeIrrad="WormIrradiationCarbone";
string typeAutomate="NoPause";
string typeMutation="WormMutationIrradiation";
double dpf=2.;
int nbf=30;
int nbWorm=1;
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
 else if(commande.find("nbWorm=")!=string::npos)
  {
  commande.replace(0,7,"");
  nbWorm=atoi(commande.data());
  cout << "nbWorm set to " << nbWorm << endl;
  }
 else if(commande.find("mutIr=")!=string::npos)
  {
  commande.replace(0,6,"");
  typeMutation=commande;
  cout << "typeMutation set to " << typeMutation << endl;
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
 a=buildTraitementWithPause(nbf,dpf,typeIrrad);
 }
else if(typeAutomate=="NoPause")
 {
 a=buildTraitementNoPause(nbf,dpf,typeIrrad);
 }
else if(typeAutomate.find("Config:")==0)
 {
 saveConfig=false;
 typeAutomate.replace(0,7,"");
 a=new Automate();
 //
 // Ajout des constructeur des Etats relatifs au Worm pour pouvoir
 // lire correctement le fichier de configuration
 //
 a->ajouteConstructeur("EtatWormImagerie",EtatWormImagerie::construire);
 a->ajouteConstructeur("EtatWormIrradiation",EtatWormIrradiation::construire);
 a->ajouteConstructeur("EtatWormBiologie",EtatWormBiologie::construire);
 a->ajouteConstructeur("EtatWormMedical",EtatWormMedical::construire);
 a->ajouteConstructeur("EtatWormPhysiqueMedicale",EtatWormPhysiqueMedicale::construire);
 a->ajouteConstructeur("EtatWormTraducteur",EtatWormTraducteur::construire);
 cout << "Lecture du fichier " << typeAutomate << endl;
 ifstream fin(typeAutomate.data());
 a->lireFichierConfiguration(fin);
 fin.close();
 size_t pos=typeAutomate.find(".pmrtConf");
 typeAutomate.replace(pos,9,"");
 a->setNom(typeAutomate);
 Jeton *jeton=new Jeton();
 jeton->setNom("Jeton");
 jeton->setCommentaire("Jeton \"patient\"");
 a->setJeton(jeton);
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
// On effectue la boucle de traitement sur tous les worms
//-----------------------------------------------------------------
vector<Jeton *> jetons;
//system("rm SuiviCartographies.txt");
for(int numWorm=1;numWorm<=nbWorm;numWorm++)
 {
 if(!(numWorm%100))
  {
  cout << "Traitement du Worm " << numWorm << endl;
  }
 bool print=(numWorm==nbWorm);
 Jeton *j=runAutomate(a,numWorm);
// system("cat SuiviCartographie.txt >> SuiviCartographies.txt");
 if(print)
  {
  printJeton(j);
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
map<string,double> wormStatus;
wormStatus["Ok    "]=0;
wormStatus["Malade"]=0;
wormStatus["Mort  "]=0;
for(itj=jetons.begin();itj!=jetons.end();itj++)
 {
 for(int i=0;i<moreData.size();i++)
  {
  fanal << moreData[i] << " ";
  }
 analyseJeton(*itj,fanal);
 WormStatus::Status st=WormStatus::kGoodShape;
 if((*itj)->getData("etatWorm",st))
  {
  switch(st)
   {
    case WormStatus::kGoodShape : wormStatus["Ok    "]++;
 				   break;
    case WormStatus::kSick :      wormStatus["Malade"]++;
 				   break;
    case WormStatus::kDead :      wormStatus["Mort  "]++;
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
for(its=wormStatus.begin();its!=wormStatus.end();its++)
 {
 cout << its->first << " : " << its->second/nbWorm*100. << " %" << endl;
 }

//-----------------------------------------------------------------
// On ecrit le fichier ".dot" de l'automate pour verifier visuellement
// l'automate
//-----------------------------------------------------------------
ofstream fout("WormAutomate.dot");
a->ecrireDotFile(fout);
fout.close();
 
//-----------------------------------------------------------------
// On ecrit le fichier de configuration de l'automate
//-----------------------------------------------------------------
if(saveConfig)
 {
 fName="Automate";
 fName+=typeAutomate;
 fName+=".pmrtConf";
 cout << "Ecriture du fichier de configuration dans : " << fName << endl;
 ofstream fconf(fName.data());
 a->ecrireFichierConfiguration(fconf);
 fconf.close();
 }

//-----------------------------------------------------------------
// C'est fini! 
//-----------------------------------------------------------------
return 0;
}
