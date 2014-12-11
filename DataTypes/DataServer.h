//
// Entete d'une classe "DataServer"
//

#ifndef DataServer_h
#define DataServer_h

#include <string>
#include <map>
#include <typeinfo>
#include <iostream>

using namespace std;

class DataServer 
{
protected:
   map<string,void *> data;
   map<string,const type_info*> dataType;
   int	debug;

public:
   DataServer(void);
   ~DataServer(void);
   
   virtual void listData(void);
   
   virtual void setDebug(int deb=0)
    {debug=deb;}
   
   template<class T> bool getData(string nom,T& dat);
   template<class T> bool setData(string nom,T& dat);

};

//_______________________________________________________
template<class T>
bool DataServer::setData(string nom,T& dat)
{
//
// Ajoute ou modifie une donnee
//
 bool res=false;
 void *d=data[nom];
 const type_info *ti=dataType[nom];
 T* dataToSet=0;
 if(d)
  {
  res=(typeid(dat) == *(dataType[nom]));
  if(res)
   {
   dataToSet=(T*)d;
   }
  }
 else
  {
  dataToSet=new T();
  dataType[nom]=&typeid(dat);
  data[nom]=(void *)dataToSet;
  res=true;
  }
 if(res)
  {
  *dataToSet=dat;
  }
 else
  {
  if(debug)
   {
   cout << "setData: La donnee \"" << nom << "\" de type (" << 
   (*(dataType[nom])).name()<< ") n'a pas le type voulu (" << 
   typeid(dat).name() << ")" <<endl;
   }
  }
 return res;
}

//_______________________________________________________
template<class T>
bool DataServer::getData(string nom,T& dat)
{
//
//recupere une donnee
//
 bool res=false;
 void *d=data[nom];
 if(d)
  {
  if(typeid(dat) == *(dataType[nom]))
   {
   dat=*((T *)d);
   //cout << typeid(dat).name() << " / " << dataType[nom]->name() << endl;
   //cout << d << " : " << dat << endl;
   res=true;
   }
  else
   {
   if(debug)
    {
    cout << "getData : La donnee \"" << nom << "\" de type (" <<
    (*(dataType[nom])).name()<< ") n'a pas le type voulu (" << 
    typeid(dat).name() << ")" <<endl;
    }
   }
  }
 else
  {
  if(debug)
   {
   cout << "getData: La donnee \"" << nom << "\" n'existe pas." << endl;
   }
  }
 return res;
}
#endif
