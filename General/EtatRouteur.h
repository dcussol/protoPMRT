//
// Classe de base d'un probleme
//

#ifndef EtatRouteur_h
#define EtatRouteur_h
#include "Etat.h"
#include <string>

using namespace std;

class EtatRouteur : public Etat
{
    protected:
    public:
     EtatRouteur(void);	
     virtual ~EtatRouteur(void);

     static Etat *construire(void) {return new EtatRouteur();}
     
     virtual Jeton *traitement(void);
     virtual Jeton *testeTraitement(bool &ok);

     virtual void lireFichierConfiguration(istream &fin,Automate *a);
     virtual void ecrireFichierConfiguration(ostream &fout);
     virtual void ecrireDotFile(ostream &fout=cout);

     virtual void setValeurParametre(string nomParam, double val);
     virtual map<string,double> getValeursParametres(void);
};

#endif    
