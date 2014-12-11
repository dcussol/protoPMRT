//
// Type de donee Cartographie
//

#ifndef Cartographie_h
#define Cartographie_h

#include <string>

using namespace std;

class Cartographie {

    protected:
     string           fNom;
     string           fCommentaire;

     virtual bool getData(void* &data,double x,double y=0,double z=0)=0;
     virtual bool setData(void* data,double x,double y=0,double z=0)=0;
    
    public:
     Cartographie(void);
     virtual ~Cartographie(void);
     
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
};
#endif
