//
// Type de donee CartographieVecteur
//

#ifndef CartographieVecteur_h
#define CartographieVecteur_h

#include <vector>
#include <typeinfo>
#include <iostream>

#include "Cartographie.h"

using namespace std;

template <class T> class CartographieVecteur : public Cartographie {

    protected:
     vector<T>    fVecteur;
     
     int          fDimX;
     int          fDimY;
     int          fDimZ;

     double       fXMin;
     double       fYMin;
     double       fZMin;

     double       fXMax;
     double       fYMax;
     double       fZMax;

     virtual bool getData(void* &data,double x,double y=0,double z=0);
     virtual bool setData(void* data,double x,double y=0,double z=0);
     
     virtual int getIndex(double x,double y=0,double z=0);
     
     virtual void setVectDim(void)
       {
       int dim=1;
       if(fDimX)
        {
	dim=fDimX;
        if(fDimY)
         {
	 dim*=fDimY;
         if(fDimZ)
          {
	  dim*=fDimZ;
	  }
	 }
	}
       fVecteur.resize(dim);
       }
    
    public:
     CartographieVecteur(void);
     virtual ~CartographieVecteur(void);
     
     virtual void setDimX(int dim) {fDimX=dim;setVectDim();}
     virtual void setDimY(int dim) {fDimY=dim;setVectDim();}
     virtual void setDimZ(int dim) {fDimZ=dim;setVectDim();}
     
     virtual int getDimX(void) {return fDimX;}
     virtual int getDimY(void) {return fDimY;}
     virtual int getDimZ(void) {return fDimZ;}
     
     virtual void setXMin(double vmin) {fXMin=vmin;}
     virtual void setYMin(double vmin) {fYMin=vmin;}
     virtual void setZMin(double vmin) {fZMin=vmin;}
     
     virtual int getXMin(void) {return fXMin;}
     virtual int getYMin(void) {return fYMin;}
     virtual int getZMin(void) {return fZMin;}

     virtual void setXMax(double vmax) {fXMax=vmax;}
     virtual void setYMax(double vmax) {fYMax=vmax;}
     virtual void setZMax(double vmax) {fZMax=vmax;}
 
     virtual int getXMax(void) {return fXMax;}
     virtual int getYMax(void) {return fYMax;}
     virtual int getZMax(void) {return fZMax;}

     template <class D> bool getData(D& data,double x,double y=0,double z=0);
     template <class D> bool setData(D& data,double x,double y=0,double z=0);
     
     virtual void print(ostream &fout=cout);    

};

//________________________________________________________
template <class T>
template <class D> 
bool CartographieVecteur<T>::getData(D& data,double x,double y,double z)
{
//
// retourne la donnee correspondant a x,y,z
//
bool ok=(typeid(D) == typeid(T));
if(ok)
 {
 void *tmp=0;
 ok=this->getData(tmp,x,y,z);
 data=*((D*)tmp);
 }
return ok;
}

//________________________________________________________
template <class T>
template <class D> 
bool CartographieVecteur<T>::setData(D& data,double x,double y,double z)
{
//
// ajuste la donnee correspondant a x,y,z
//
bool ok=(typeid(D) == typeid(T));
if(ok)
 {
 ok=this->setData((void *)(&data),x,y,z);
 }
return ok;
}

//________________________________________________________
template <class T>
CartographieVecteur<T>::CartographieVecteur(void):Cartographie()
{
//
// Constructeur par defaut
//
fNom="CartographieVecteur";
fCommentaire="CartographieVecteur de base";
fVecteur.clear();
fDimX=0;
fDimY=0;
fDimZ=0;
fXMin=0;
fYMin=0;
fZMin=0;
fXMax=0;
fYMax=0;
fZMax=0;
}

//________________________________________________________
template <class T>
CartographieVecteur<T>::~CartographieVecteur(void)
{
//
// Destructeur
//
}

//________________________________________________________
template <class T>
bool CartographieVecteur<T>::getData(void* &data,double x,double y,double z)
{
//
// recupere la donnee correspondant a x,y,z
//
bool ok=false;
int i=this->getIndex(x,y,z);
if (i>=0 && i<fVecteur.size())
 {
 data=(void *)&fVecteur[i];
 ok=true;
 }
return ok;
}

//________________________________________________________
template <class T>
bool CartographieVecteur<T>::setData(void* data,double x,double y,double z)
{
//
// ajuste la donnee correspondant a x,y,z
//
bool ok=false;
int i=this->getIndex(x,y,z);
if (i>=0 && i<fVecteur.size())
 {
 fVecteur[i]=*((T *)data);
 ok=true;
 }
return ok;
}

//________________________________________________________
template <class T>
int CartographieVecteur<T>::getIndex(double x,double y,double z)
{
//
// Retourne l'index correspondant a x,y,z
//
int index=-1;
if(x>=fXMin && x<=fXMax)
 {
 int iy=0;
 int iz=0;
 int ix=(int)((x-fXMin)*fDimX/(fXMax-fXMin));
 if(fDimY && y>=fYMin && y<=fYMax)
  {
  iy=(int)((y-fYMin)*fDimY/(fYMax-fYMin));
  if(fDimZ && z>=fZMin && z<=fZMax)
   {
   iz=(int)((z-fZMin)*fDimZ/(fZMax-fZMin));
   }
  }
 index=ix+fDimX*(iy+fDimY*iz);
 }
return index;
}

//________________________________________________________
template <class T>
void CartographieVecteur<T>::print(ostream &fout)
{
//
// Impression de la cartographie dans un fichier
//
for(int i=0;i<fVecteur.size();i++)
 {
 fout << i << " " << fVecteur[i] << endl;
 }
}    
#endif
