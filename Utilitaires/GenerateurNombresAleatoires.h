//
// Classe generateur de nombre aleatoires
//

#ifndef GenerateurNombresAleatoires_h
#define GenerateurNombresAleatoires_h

#include <random>

using namespace std;

class GenerateurNombresAleatoires
{
 private:
  static GenerateurNombresAleatoires *fGNA;
  
  mt19937                generateur;

  GenerateurNombresAleatoires(void);
  
 
 public:
  ~GenerateurNombresAleatoires(void);
  
  static GenerateurNombresAleatoires *getGenerateurNombresAleatoires(void)
   {
   if(!fGNA)
    {
    fGNA=new GenerateurNombresAleatoires();
    }
   return fGNA;
   }
   
  virtual double getRandom(void);
  virtual int getPoisson(double moyenne);

};

#endif
