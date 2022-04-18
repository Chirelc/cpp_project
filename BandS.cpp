#include <iostream>
#include <random>
//#include <chrono>
#include <tgmath.h>
#include <list>
#include<algorithm>
const double  prixStrikeK=60.00;
const double tauxR=0.02;
const long periodT=1;
const S_0=100;

/*int simulation_trajectoire_mvt_brownien(){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  normal_distribution<double> distribution(0.0,1.00);
  G=distribution(generator);
  return
}*/
/*************SANS DIVIDENDE **********************/
double calculerD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
// on gener le process pour variable normal N(d1)
return (log(prixSt/prixStrikek)+(tauxR+(pow(ecartType,2.00)/2)*periodT))/(ecartType*sqrt(periodT));

}
double calculerLoiNormaleD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  double d1= calculerD1( prixSt, ecartType, periodT, tauxR, prixStrikeK);
  normal_distribution<double> distribution(0.0,d1);
  double N = generator(distribution);
  return N;
}
double calculerD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK){
double d1=calculerLoiNormaleD1(prixSt, ecartType, periodT, tauxR, prixStrikeK);
return d1-(ecartType*sqrt(periodT));
}
double calculerLoiNormaleD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  double d2= calculerD2( prixSt, ecartType, periodT, tauxR, prixStrikeK);
  normal_distribution<double> distribution(0.0,d2);
  double N = generator(distribution);
  return N;
}
double getPrixCall(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK){
  double Nd1=calculerLoiNormaleD1(prixSt,ecartType,periodT,  tauxR, prixStrikeK);
  double Nd2=calculerLoiNormaleD2(prixSt,ecartType,periodT,  tauxR, prixStrikeK);
  return (prixSt*Nd1)-(prixStrikeK*exp(-tauxR*periodT)*Nd2);
}
double getPrixPut(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende){
  double Nd1= - calculerLoiNormaleD1(prixSt,ecartType,periodT,  tauxR, prixStrikeK);
  double Nd2= - calculerLoiNormaleD2(prixSt,ecartType,periodT,  tauxR, prixStrikeK);
  return (prixStrikeK*exp(-tauxR*periodT)*Nd2)-(prixSt*Nd1);
}
/*double getSensibiliteDelta();
double getSensibiliteGamma();
double getSensibiliteVega();
double getSensibiliteRho();
double getSensibiliteThega();*/
int main(){

}
