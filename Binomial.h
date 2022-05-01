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
long n;
public:
Binomial(double ecartType,double prixS0,double prixStrikeK,double tauxR,long periodT,long n);
double calculerProbabiliteHausseU();
double calculerProbabiliteBaisseD();
vector<vector<double> > calculerPrixSt();
vector<vector<double> > calculerPayOffs(bool isCall);
double getPrixCall();
double getPrixPut();
};
