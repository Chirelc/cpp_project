#include <iostream>
#include <random>
//#include <chrono>
#include <tgmath.h>
#include <list>
#include<algorithm>
const double  prixStrikeK=60.00;
const double tauxR=0.02;
const long periodT=1;
int simulation_trajectoire_mvt_brownien(deltaPeriod){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  normal_distribution<double> distribution(0.0,deltaPeriod);
  G=distribution(generator);

}
/*double calculerD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double calculerD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double calculerLoiNormaleD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double calculerLoiNormaleD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende);
double getPrixCall(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende)
double getPrixPut(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK, double dividende)
double getSensibiliteDelta();
double getSensibiliteGamma();
double getSensibiliteVega();
double getSensibiliteRho();
double getSensibiliteThega();*/
int main(){

}
