#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
class Parite{
public:
double prixSt;
double prixStrikeK;
double prixCall;
double prixPut;
double tauxR;
long periodT;
public:
Parite(double prixSt,double prixStrikeK,double prixCall,double prixPut,double tauxR,long periodT);
bool isValueOk();
};
Parite::Parite(double prixSt,double prixStrikeK,double prixCall,double prixPut,double tauxR,long periodT){
  this->prixSt=prixSt;
  this->prixStrikeK=prixStrikeK;
  this->prixCall=prixCall;
  this->prixPut=prixPut;
  this->tauxR=tauxR;
  this->periodT=periodT;
}
bool Parite::isValueOk(){
  bool res=false;

if(prixCall>prixPut){
  //St ou S0?
  if(prixCall<prixSt){
    res=true;
  }
  double v = max(prixSt-prixStrikeK*exp(-tauxR*periodT),0.00);
  if(prixCall > v){
    res=true;
  }
}else{
  if(prixPut<prixStrikeK*exp(-tauxR*periodT)){
    res=true;
  }
  double v =max(prixStrikeK*exp(-tauxR*periodT-prixSt)- prixSt,0.00);
  if(prixPut>v){
    res=true;
  }
}
return res;
}

/*int main(){
double prixSt=1;
double prixStrikeK=100;
double prixCall= 0.0002077;
double tauxR=1;
long periodT=1;
double prixPut= 35.7882;
Parite p =Parite(prixSt,prixStrikeK,prixCall, prixPut,tauxR,periodT);
cout<<p.isValueOk();

}*/
