#include <iostream>
#include <random>
//#include <chrono>
#include <tgmath.h>
#include <list>
#include<algorithm>
using namespace std;
const double ecartType=0.25;
const long periodT=1;
const double prixS0=100;
const double prixStrikeK=60.00;
const double tauxR=0.02;
// reprendre monte carlos pour calculer le payoff (call )
//chercher u et d
double calculerProbabiliteHausseU(double ecartType, long periodT){
return exp(ecartType*sqrt(periodT));
}
double calculerProbabiliteBaisseD(double ecartType, long periodT){
  return exp(-(ecartType*sqrt(periodT)));
}
// j'ai ajouté prixStrike
//ajout isCall or pUT
double calculerPayOffHausseU(double prixS0, double ecartType, long periodT,double prixStrikeK,bool isCall){
double p=prixS0*calculerProbabiliteHausseU( ecartType,periodT);
double payOffHausseU;
if(isCall){
 payOffHausseU= max(p-prixStrikeK,0.0);
}else{
    payOffHausseU =max(prixStrikeK-p,0.0);
}
return payOffHausseU;

}
double calculerPayOffBaisseD(double prixS0, double ecartType, long periodT,double prixStrikeK,bool isCall){
  double p=prixS0*calculerProbabiliteBaisseD(ecartType,periodT);
  double payOffBaisseD;
  if(isCall){
  payOffBaisseD=max(p-prixStrikeK,0.0);
  }else{
    payOffBaisseD=max(prixStrikeK-p,0.0);
  }
  return payOffBaisseD;
}
double getPrixCall(double prixS0, double ecartType, long periodT, double tauxR, double prixStrikeK){
bool isCall=true;
double  p= (exp(-tauxR*periodT)-calculerProbabiliteBaisseD(ecartType,periodT))/(calculerProbabiliteHausseU(ecartType,periodT)-calculerProbabiliteBaisseD(ecartType,periodT));
double   prixCall= exp(-tauxR*periodT)*(p*calculerPayOffHausseU(prixS0, ecartType,periodT, prixStrikeK,isCall)+(1-p)*calculerPayOffBaisseD(prixS0, ecartType,periodT, prixStrikeK,isCall));
  return prixCall;
}

double getPrixPut(double prixS0, double ecartType, long periodT, double tauxR, double prixStrikeK){
  bool isCall=false;
  double  p= (exp(-tauxR*periodT)-calculerProbabiliteBaisseD(ecartType,periodT))/(calculerProbabiliteHausseU(ecartType,periodT)-calculerProbabiliteBaisseD(ecartType,periodT));
  double prixPut = exp(-tauxR*periodT)*(p*calculerPayOffHausseU(prixS0, ecartType,periodT, prixStrikeK,isCall)+(1-p)*calculerPayOffBaisseD(prixS0, ecartType,periodT, prixStrikeK,isCall));
     return prixPut;
}
int main(){
double priceP = getPrixPut(prixS0,  ecartType, periodT,  tauxR,  prixStrikeK);
cout<<"prix du put: "<<priceP<<"\n";
/*double payOffCb= calculerPayOffBaisseD( prixS0, ecartType,periodT, prixStrikeK,true);
double payOffCh= calculerPayOffHausseU( prixS0, ecartType,periodT, prixStrikeK,true);
cout<<"payOff baisse:"<<payOffCb<<" ";
cout<<"payOff hausse "<<payOffCh<<" ";*/
double priceC = getPrixCall(prixS0,  ecartType, periodT,  tauxR,  prixStrikeK);
cout<<"prix du call: "<<priceC<<"\n";
}
