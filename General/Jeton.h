//
// Classe de base d'un probleme
//

#ifndef Jeton_h
#define Jeton_h

#include "DataServer.h"

#include <string>

using namespace std;

class Jeton
{
    protected:
     string           fNom;
     string           fCommentaire;
     
     DataServer       *fDataServer;

    public:
     Jeton(void);	
     virtual ~Jeton(void);
     
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

   template<class T> bool getData(string nom,T& dat);
   template<class T> bool setData(string nom,T& dat);
   
   virtual void listData(void)
    {fDataServer->listData();}

};

//_______________________________________________________
template<class T>
bool Jeton::setData(string nom,T& dat)
{
//
// Ajoute ou modifie une donnee
//
 return fDataServer->setData(nom,dat);
}

//_______________________________________________________
template<class T>
bool Jeton::getData(string nom,T& dat)
{
//
// Ajoute ou modifie une donnee
//
 return fDataServer->getData(nom,dat);
}

#endif    
