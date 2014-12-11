//
// implementation de DataServer
//

#include "DataServer.h"
#include <iostream>

using namespace std;

//_______________________________________________________
DataServer::DataServer(void)
{
//
// Constructeur
//
 data.clear();
 dataType.clear();
 debug=0;
}

//_______________________________________________________
DataServer::~DataServer(void)
{
//
// Destructeur
//
 data.clear();
 dataType.clear();
}

//_______________________________________________________
void DataServer::listData(void)
{
//
// Liste des donnes du DataServer
//
map<string,void *>::iterator it;
for(it=data.begin();it!=data.end();it++)
 {
 cout << it->first << " : " << (*(dataType[it->first])).name() << 
 endl;
 }
}
