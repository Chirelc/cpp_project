
#include "BandS.h"
#include <iostream>
#include <random>
#include <tgmath.h>
#include <list>
#include <math.h>
#include<algorithm>
#include <cstdlib>
using namespace std;
  BandS::BandS(double n,double prixSt, double ecartType, double  periodT, double tauxR, double prixStrikeK){
    this->n=n;
    this->ecartType=ecartType;
    this->periodT=periodT;
    this->tauxR=tauxR;
    this->prixStrikeK=prixStrikeK;
    this->prixSt=prixSt;
  }
  double BandS::calculerLoiNormaleNonCummule( double x){
      return (1.0/(pow(2*3.14,0.5)))*exp(-0.5*x*x);
  }

double BandS::calculerD1(){
return (log(prixSt/prixStrikeK)+(tauxR+(pow(ecartType,2.00)/2)*periodT))/(ecartType*sqrt(periodT));
}

double BandS::calculerD1(double dividende){
  return (log(prixSt/prixStrikeK)+(tauxR - dividende +(pow(ecartType,2.00)/2)*periodT))/(ecartType*sqrt(periodT));
}
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
  double d2=calculerD2( );
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
  double d2=-calculerD2( );
  double Nd1= calculerLoiNormale(d1);
  double Nd2= calculerLoiNormale(d2);
  return (prixStrikeK*exp(-tauxR*periodT)*Nd2)-(prixSt*exp(-dividende*periodT)*Nd1);
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
    return exp(-dividende*periodT)*(calculerLoiNormale(d1));
  }else{
    return exp(-dividende*periodT)*(calculerLoiNormale(d1)-1);
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
  return prixSt*exp(-dividende*periodT)*calculerLoiNormaleNonCummule(d1)*sqrt(periodT);
}
double BandS::getSensibiliteTheta(bool isCall){
  double d1=calculerD1();
  double d2=calculerD2();
  if(isCall){
    return -((prixSt*calculerLoiNormaleNonCummule(d1)*ecartType)/(2*sqrt(periodT)))-tauxR*prixStrikeK*exp(-tauxR*periodT)*calculerLoiNormale(d2);
  }else{
  return -((prixSt*calculerLoiNormaleNonCummule(d1)*ecartType)/(2*sqrt(periodT)))+tauxR*prixStrikeK*exp(-tauxR*periodT)*calculerLoiNormale(-d2);
  }
}
double BandS::getSensibiliteTheta(bool isCall,double dividende ){
  double d1=calculerD1(dividende);
  double d2=calculerD2(dividende);
  if(isCall){
      return -(prixSt*exp(-dividende*periodT)*calculerLoiNormaleNonCummule(d1)*ecartType)/(2*sqrt(periodT))-tauxR*prixStrikeK*exp(-tauxR*periodT)*calculerLoiNormale(d2)+dividende*prixSt*exp(-dividende*periodT)*calculerLoiNormale(d1);
  }else{
  return -(prixSt*exp(-dividende*periodT)*calculerLoiNormaleNonCummule(d1)*ecartType)/(2*sqrt(periodT))+tauxR*prixStrikeK*exp(-tauxR*periodT)*calculerLoiNormale(-d2)-dividende*prixSt*exp(-dividende*periodT)*calculerLoiNormale(-d1);
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
  bool res;
  if((getPrixCall()-getPrixPut())==(prixSt-prixStrikeK*exp(-tauxR*periodT))){
    res=true;
  }else{
    res=false;
  }
  cout<<"1: "<<getPrixCall()-getPrixPut();
  cout<<"2: "<<(prixSt-prixStrikeK*exp(-tauxR*periodT));
return res;
}

bool BandS::getParite(double dividende){
  bool res;
  if((getPrixCall(dividende)-getPrixPut(dividende))==(prixSt-prixStrikeK*exp(-tauxR*periodT))){
    res=true;
  }else{
    res=false;
  }
  cout<<"1: "<<getPrixCall(dividende)-getPrixPut(dividende);
  cout<<"2: "<<(prixSt-prixStrikeK*exp(-tauxR*periodT));
return res;
}
