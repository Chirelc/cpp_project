#include <iostream>
#include <random>
//#include <chrono>
#include <tgmath.h>
#include <list>
#include<algorithm>
using namespace std;
/*const double ecartType=0.25;
const long periodT=1;
const double prixS0=100;
const double prixStrikeK=60.00;
const double tauxR=0.02;*/
class Binomial{
private:
double ecartType;
double prixS0;
double prixStrikeK;
double tauxR;
long periodT;
public:
Binomial(double ecartType,double prixS0,double prixStrikeK,double tauxR,long periodT);
double calculerProbabiliteHausseU();
double calculerProbabiliteBaisseD();
double calculerPayOffHausseU(bool isCall);
double calculerPayOffBaisseD(bool isCall);
double getPrixCall();
double getPrixPut();
};
Binomial::Binomial(double ecartType,double prixS0,double prixStrikeK,double tauxR,long periodT){
  this->ecartType=ecartType;
  this->prixS0=prixS0;
  this->prixStrikeK=prixStrikeK;
  this->tauxR=tauxR;
  this->periodT=periodT;
}
double Binomial::calculerProbabiliteHausseU(){
return exp(ecartType*sqrt(periodT));
}
double Binomial::calculerProbabiliteBaisseD(){
  return exp(-(ecartType*sqrt(periodT)));
}
// j'ai ajouté prixStrike
//ajout isCall or pUT
double Binomial::calculerPayOffHausseU(bool isCall){
double p=prixS0*calculerProbabiliteHausseU();
double payOffHausseU;
if(isCall){
 payOffHausseU= max(p-prixStrikeK,0.0);
}else{
    payOffHausseU =max(prixStrikeK-p,0.0);
}
return payOffHausseU;

}
double Binomial::calculerPayOffBaisseD(bool isCall){
  double p=prixS0*calculerProbabiliteBaisseD();
  double payOffBaisseD;
  if(isCall){
  payOffBaisseD=max(p-prixStrikeK,0.0);
  }else{
    payOffBaisseD=max(prixStrikeK-p,0.0);
  }
  return payOffBaisseD;
}
double Binomial::getPrixCall(){
bool isCall=true;
double  p= (exp(-tauxR*periodT)-calculerProbabiliteBaisseD())/(calculerProbabiliteHausseU()-calculerProbabiliteBaisseD());
double   prixCall= exp(-tauxR*periodT)*(p*calculerPayOffHausseU(isCall)+(1-p)*calculerPayOffBaisseD(isCall));
  return prixCall;
}

double Binomial::getPrixPut(){
  bool isCall=false;
  double  p= (exp(-tauxR*periodT)-calculerProbabiliteBaisseD())/(calculerProbabiliteHausseU()-calculerProbabiliteBaisseD());
  double prixPut = exp(-tauxR*periodT)*(p*calculerPayOffHausseU(isCall)+(1-p)*calculerPayOffBaisseD(isCall));
     return prixPut;
}
int main(){
Binomial obj = Binomial(0.25,100.00,60.00,0.02,1);
double priceP = obj.getPrixPut();
cout<<"prix du put: "<<priceP<<"\n";
/*double payOffCb= calculerPayOffBaisseD( prixS0, ecartType,periodT, prixStrikeK,true);
double payOffCh= calculerPayOffHausseU( prixS0, ecartType,periodT, prixStrikeK,true);
cout<<"payOff baisse:"<<payOffCb<<" ";
cout<<"payOff hausse "<<payOffCh<<" ";*/
double priceC = obj.getPrixCall();
cout<<"prix du call: "<<priceC<<"\n";
}
