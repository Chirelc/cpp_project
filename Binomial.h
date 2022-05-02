#include <vector>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
#include<algorithm>
using namespace std;
class Binomial{
private:
double ecartType;
double prixS0;
double prixStrikeK;
double tauxR;
long periodT;
double  n;
public:
Binomial(double ecartType,double prixS0,double prixStrikeK,double tauxR,long periodT,long n);
double calculerProbabiliteHausseU();
double calculerProbabiliteBaisseD();
vector<vector<double> > calculerPrixSt();
vector<vector<double> > calculerPayOffs(bool isCall);
double getPrixCall();
double getPrixPut();
};
