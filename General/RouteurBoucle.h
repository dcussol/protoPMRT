//
// Classe de base d'une RouteurBoucle
//

#ifndef RouteurBoucle_h
#define RouteurBoucle_h

class Etat;
class Etat;
#include "Routeur.h"

#include <string>

using namespace std;

class RouteurBoucle : public Routeur
{
    protected:
     int	fCountInit;
     int	fCount;

     Etat        *fEtatBoucle;
     Etat        *fEtatSortie;

    public:
     RouteurBoucle(void);	
     virtual ~RouteurBoucle(void);
     
     static Routeur *construire(void) {new RouteurBoucle();}

     virtual void setCompteurInitial(int c)
      {
      fCountInit=c;
      fCount=c;
      }
     virtual int getCompteurInitial(void)
      {
      return fCountInit;
      }
     virtual int getCompteur(void)
      {
      return fCount;
      }

     virtual void setEtatBoucle(Etat *e)
      {
      fEtatBoucle=e;
      }
     virtual Etat *getEtatBoucle(void)
      {
      return fEtatBoucle;
      }
     
     virtual void setEtatSortie(Etat *e)
      {
      fEtatSortie=e;
      }
     virtual Etat *getEtatSortie(void)
      {
      return fEtatSortie;
      }
     
     virtual Etat *suivant(void);

     virtual vector<Etat *> getSuivants(void)
      {
      fSuivants.clear();
      fSuivants.push_back(fEtatBoucle);
      fSuivants.push_back(fEtatSortie);
      return fSuivants;
      }

     virtual void lireFichierConfiguration(istream &fin,Automate *a);
     virtual void ecrireFichierConfiguration(ostream &fout=cout);
     virtual void ecrireDotFile(ostream &fout=cout);
     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["CompteurInitial"]=(double)fCountInit;
      return lstParam;}
     virtual void setValeurParametre(string nomParam, double val)
      {
      if(nomParam=="CompteurInitial")
       {
       this->setCompteurInitial((int)val);
       }
      }
};

#endif    
