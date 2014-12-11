//
// Classe de base d'une Visiteur
//

#ifndef Visiteur_h
#define Visiteur_h

class Etat;

#include <string>

using namespace std;

class Visiteur
{
    protected:
     string           fNom;
     string           fCommentaire;
     
     Etat 	*fEtat;

    public:
     Visiteur(void);	
     virtual ~Visiteur(void);
     
     virtual void setNom(string nom)
      {
      fNom=nom;
      }
     virtual string getNom(void)
      {
      return fNom;
      }

     virtual void setCommentaire(string comment)
      {
      fCommentaire=comment;
      }
     virtual string getCommentaire(void)
      {
      return fCommentaire;
      }
      
     virtual void setEtat(Etat *e)
      {
      fEtat=e;
      }
     virtual Etat *getEtat(void)
      {
      return fEtat;
      }
     

     virtual void initialisation(void)=0;
     virtual void preTraitement(void)=0;
     virtual void postTraitement(void)=0;
     virtual void finalisation(void)=0;
};

#endif    
