//
// Classe d'imagerie du Amibe
//

#ifndef AmibeIrradiation_h
#define AmibeIrradiation_h

#include "Strategie.h"
#include "CartographieVecteur.h"

#include <tuple>

class AmibeIrradiation : public Strategie
{
    protected:
     double doseParFrac;
     int    nombreDeFrac;
     double doseTraitement;

     CartographieVecteur<double> doseFraction;
     CartographieVecteur<double> doseTotale;
     CartographieVecteur<string> zones;
     
     vector<tuple<double,double,double>>  fFaisceaux;
     double      fXCentre;
     double      fYCentre;
     
     string	 fNomFichierFaisceaux;


   public:
     AmibeIrradiation(void);
     ~AmibeIrradiation(void);
      
     virtual Jeton *resoudre(Jeton *j);

     virtual bool peutOperer(Jeton *j);
     virtual Jeton *genereDonnee(Jeton *j);
     
     virtual void setNomFichierFaisceaux(string fNom)
      {fNomFichierFaisceaux=fNom;}
      
     virtual bool setValeurParametre(string nomParam,double valeur);
     virtual map<string,double> getValeursParametres(void) 
      {map<string,double> lstParam; 
      lstParam["doseParFrac"]=doseParFrac;
      return lstParam;}
     
     virtual void setIsoCentre(double x, double y)
      {fXCentre=x;fYCentre=y;}
     virtual void addFaisceau(double poids, double angle,double largeur)
      {tuple<double,double,double> faisceau(poids,angle,largeur);
      fFaisceaux.push_back(faisceau);}
     virtual bool getRfromXYThetaL(double&r, double x, double y, double r0,
                                   double theta, double largeur);
				   
     virtual void lireFichierFaisceaux(bool print=false);
};

#endif
