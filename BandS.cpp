#include <iostream>
#include <random>
//#include <chrono>
#include <tgmath.h>
#include<algorithm>
#include <iomanip>
#include <cmath>
#include "Parite.cpp"
using namespace std;
class BandS{
private :
  double prixStrikeK;
  double tauxR;
  double ecartType;
  long periodT;
  double S_0;
  double prixSt;
public:
BandS(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK);
//int simulation_trajectoire_mvt_brownien();
double calculerD1( double dividende);
double calculerD2(double dividende);
double calculerD1();
double calculerD2();
double calculerLoiNormale(double var);
double getPrixCall( double dividende);
double getPrixPut( double dividende);
double getPrixCall();
double getPrixPut();
double calculerLoiNormaleNonCummule(double var);
double getSensibiliteDelta(bool isCall);
double getSensibiliteGamma();
double getSensibiliteVega();
double getSensibiliteRho(bool isCall);
double getSensibiliteTheta(bool isCall);
double getSensibiliteDelta(bool isCall,double dividende);
double getSensibiliteGamma(double dividende);
double getSensibiliteVega(double dividende);
double getSensibiliteRho(bool isCall,double dividende);
double getSensibiliteTheta(bool isCall,double dividende);
bool getParite();
bool getParite(double dividende);
};


/*int simulation_trajectoire_mvt_brownien(){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  normal_distribution<double> distribution(0.0,1.00);
  G=distribution(generator);
  return
}*/
/*************SANS DIVIDENDE **********************/
  BandS::BandS(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK){
    this->prixSt=prixSt;
    this->ecartType=ecartType;
    this->periodT=periodT;
    this->tauxR=tauxR;
    this->prixStrikeK=prixStrikeK;
  }

double BandS::calculerD1(){
return (log(prixSt/prixStrikeK)+(tauxR+(pow(ecartType,2.00)/2)*periodT))/(ecartType*sqrt(periodT));
}

double BandS::calculerD1(double dividende){
  return (log(prixSt/prixStrikeK)+(tauxR - dividende +(pow(ecartType,2.00)/2)*periodT))/(ecartType*sqrt(periodT));
}
/*double calculerLoiNormaleD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  double d1= calculerD1( prixSt, ecartType, periodT, tauxR, prixStrikeK);
  normal_distribution<double> distribution(0.0,d1);
  double N = generator(distribution);
  return N;
}*/
/*double BandS::calculerLoiNormaleD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  double d2= calculerD2( prixSt, ecartType, periodT, tauxR, prixStrikeK);
  normal_distribution<double> distribution(0.0,d2);
  double N = generator(distribution);
  return N;
}*/

double BandS::calculerD2(){
double d1=calculerD1();
return d1-(ecartType*sqrt(periodT));
}
double BandS::calculerD2(double dividende){
  double d1=calculerD1(dividende);
  return d1-(ecartType*sqrt(periodT));
}
double BandS::calculerLoiNormale(double var)
{
    return erfc(-var / sqrt(2))/2;
}

double BandS::getPrixCall(){
  double d1=calculerD1();
  double d2=calculerD2();
  double Nd1=calculerLoiNormale(d1);
  double Nd2=calculerLoiNormale(d2);
  return (prixSt*Nd1)-(prixStrikeK*exp(-tauxR*periodT)*Nd2);
}
double BandS::getPrixPut( ){
  double d1=-calculerD1();
  double d2=-calculerD2();
  double Nd1= calculerLoiNormale(d1);
  double Nd2= calculerLoiNormale(d2);
  return (prixStrikeK*exp(-tauxR*periodT)*Nd2)-(prixSt*Nd1);
}
double BandS::getPrixCall(double dividende){
  double d1= calculerD1(dividende);
  double d2=calculerD2(dividende);
  double Nd1=calculerLoiNormale(d1);
  double Nd2=calculerLoiNormale(d2);
  return (prixSt*exp(-dividende*periodT)*Nd1)-(prixStrikeK*exp(-tauxR*periodT)*Nd2);
}
double BandS::getPrixPut(double dividende){
  double d1=-calculerD1();
  double d2=-calculerD2();
  double Nd1= calculerLoiNormale(d1);
  double Nd2= calculerLoiNormale(d2);
  return (prixStrikeK*exp(-tauxR*periodT)*Nd2)-(prixSt*exp(-dividende*periodT)*Nd1);
}

double BandS::calculerLoiNormaleNonCummule(double var){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  normal_distribution<double> distribution(0.0,var);
  double G=distribution(generator);
  //cout<<"ln: "<<G;
  return G ;
}

double BandS::getSensibiliteDelta(bool isCall){
  double d1=calculerD1();
  if(isCall){
    return calculerLoiNormale(d1);
  }else{
    return calculerLoiNormale(d1) - 1;
  }
}

double BandS::getSensibiliteDelta(bool isCall,double dividende){
    double d1=calculerD1(dividende);
  if(isCall){
    return calculerLoiNormale(d1);
  }else{
    return calculerLoiNormale(d1) - 1;
  }
}

double BandS::getSensibiliteGamma(){
  double d1=calculerD1();
  return calculerLoiNormaleNonCummule(d1)/(prixSt*ecartType*sqrt(periodT));

}
double BandS::getSensibiliteGamma(double dividende){
  double d1=calculerD1(dividende);
  return calculerLoiNormaleNonCummule(d1)/(prixSt*ecartType*sqrt(periodT));

}
double BandS::getSensibiliteVega(){
  double d1=calculerD1();
  return prixSt*calculerLoiNormaleNonCummule(d1)*sqrt(periodT);
}

double BandS::getSensibiliteVega(double dividende){
  double d1=calculerD1(dividende);
  return prixSt*calculerLoiNormaleNonCummule(d1)*sqrt(periodT);
}
double BandS::getSensibiliteTheta(bool isCall){
  double d1=calculerD1();
  double d2=calculerD2();
  if(isCall){
      return (prixSt*calculerLoiNormaleNonCummule(d1)*ecartType)/(2*sqrt(periodT))+tauxR*prixStrikeK*exp(-tauxR*periodT)*calculerLoiNormale(d2);
  }else{
  return -(prixSt*calculerLoiNormaleNonCummule(d1)*ecartType)/(2*sqrt(periodT))-tauxR*prixStrikeK*exp(-tauxR*periodT)*calculerLoiNormale(d2);
  }
}
double BandS::getSensibiliteTheta(bool isCall,double dividende ){
  double d1=calculerD1(dividende);
  double d2=calculerD2(dividende);
  if(isCall){
      return (prixSt*calculerLoiNormaleNonCummule(d1)*ecartType)/(2*sqrt(periodT))+tauxR*prixStrikeK*exp(-tauxR*periodT)*calculerLoiNormale(d2);
  }else{
  return -(prixSt*calculerLoiNormaleNonCummule(d1)*ecartType)/(2*sqrt(periodT))-tauxR*prixStrikeK*exp(-tauxR*periodT)*calculerLoiNormale(d2);
  }
}
double BandS::getSensibiliteRho(bool isCall){
  double d1=calculerD1();
  double d2=calculerD2();
  double Md2=-calculerD2();
  if(isCall){
    return prixStrikeK*periodT*exp(-tauxR*periodT)*calculerLoiNormale(d2);
  }else{
    return -prixStrikeK*periodT*exp(-tauxR*periodT)*calculerLoiNormale(Md2);
  }

}
double BandS::getSensibiliteRho(bool isCall,double dividende){
  double d1=calculerD1(dividende);
  double d2=calculerD2(dividende);
  double Md2=-calculerD2(dividende);
  if(isCall){
    return prixStrikeK*periodT*exp(-tauxR*periodT)*calculerLoiNormale(d2);
  }else{
    return -prixStrikeK*periodT*exp(-tauxR*periodT)*calculerLoiNormale(Md2);
  }

}
bool BandS::getParite(){
Parite p= Parite(prixSt,prixStrikeK,getPrixCall(), getPrixPut(),tauxR,periodT);
bool res;
res=p.isValueOk();
return res;
}

bool BandS::getParite(double dividende){
Parite p= Parite(prixSt,prixStrikeK,getPrixCall(dividende), getPrixPut(dividende),tauxR,periodT);
bool res;
res=p.isValueOk();
return res;
}

/*int main(){
double prixSt=100.00;
double prixStrikeK=60.00;
double tauxR=0.02;
double ecartType=0.25;
long periodT=1;
BandS obj = BandS(prixSt,ecartType,periodT,tauxR,prixStrikeK);
double d1=obj.calculerD1();
obj.calculerLoiNormaleNonCummule(d1);
double call=obj.getPrixCall();
double put= obj.getPrixPut();
cout<<"put :"<<put;
cout<<"call :"<<call;

}*/
