//
// Utilitaire permettant de separer une string selon un separateur
//

#include <string>
#include <vector>

using namespace std; 

vector<string> splitString(string sToSplit, string sep="/")
{
vector<string> splittedString;
size_t lastFound=0;
size_t found = sToSplit.find(sep);
while(found!=string::npos)
 {
 splittedString.push_back(sToSplit.substr(lastFound,found-lastFound));
 lastFound=found+sep.length();
 found = sToSplit.find(sep,lastFound);
 }
splittedString.push_back(sToSplit.substr(lastFound,sToSplit.length()-lastFound));
return splittedString;
}
