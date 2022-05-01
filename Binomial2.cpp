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
class Binomial2{
private:
double ecartType;
double prixS0;
double prixStrikeK;
double tauxR;
long periodT;
long n;
public:
Binomial2(double ecartType,double prixS0,double prixStrikeK,double tauxR,long periodT,long n);
double calculerProbabiliteHausseU();
double calculerProbabiliteBaisseD();
vector<vector<double> > calculerPrixSt();
vector<vector<double> > calculerPayOffs(bool isCall);
double getPrixCall();
double getPrixPut();
};
Binomial2::Binomial2(double ecartType,double prixS0,double prixStrikeK,double tauxR,long periodT,long n ){
  this->ecartType=ecartType;
  this->prixS0=prixS0;
  this->prixStrikeK=prixStrikeK;
  this->tauxR=tauxR;
  this->periodT=periodT;
  this->n=n;
}

double Binomial2::calculerProbabiliteHausseU(){
return exp(ecartType*sqrt(periodT/n));
}
double Binomial2::calculerProbabiliteBaisseD(){
  return exp(-(ecartType*sqrt(periodT/n)));
}
// j'ai ajouté prixStrike
//ajout isCall or pUT
vector<vector<double> > Binomial2::calculerPrixSt(){
vector<vector<double> > prixSt(n + 1, vector<double>(n + 1, 0));
double d=calculerProbabiliteBaisseD();
double u=calculerProbabiliteHausseU();
for (int j = 0; j <= n; j++) {
     for (int i = 0; i <= j; i++) {
         prixSt [i][j] = prixS0*pow(u, j - i)*pow(d, i);
     }
 }
return prixSt;
}
vector<vector<double> > Binomial2::calculerPayOffs(bool isCall){
vector<vector<double> >  valeurSt=calculerPrixSt();
vector<vector<double> >  prixArbre(n + 1, vector<double>(n + 1, 0));
 for (int i = 0; i <= n; i++) {
   if(isCall){
   prixArbre [i][n]=max(valeurSt[i][n] - prixStrikeK, 0.0);
 }else{
   prixArbre [i][n]=max(prixStrikeK-valeurSt[i][n], 0.0);
 }

 }
  return prixArbre;
}

/*double Binomial::calculerPayOffHausseU(bool isCall){
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
// a refaire avec plus de periodes -> fonction recurante ?*/
double Binomial2::getPrixCall(){
double dt= periodT/n;
double Call;
double  p= (exp(-tauxR*periodT)-calculerProbabiliteBaisseD())/(calculerProbabiliteHausseU()-calculerProbabiliteBaisseD());
vector<vector<double > > prixArbre = calculerPayOffs(true);
for (int j = n - 1; j >= 0; j--) {
  for (int i = 0; i <= j; i++) {
    prixArbre[i][j] = exp(-tauxR*dt)*(p*prixArbre[i][j + 1] + (1 - p)*prixArbre[i + 1][j + 1]);
    }
  }
  return prixArbre[0][0];
}

double Binomial2::getPrixPut(){
  double dt= periodT/n;
  double  p= (exp(-tauxR*periodT)-calculerProbabiliteBaisseD())/(calculerProbabiliteHausseU()-calculerProbabiliteBaisseD());
  vector<vector<double > > prixArbre = calculerPayOffs(false);
  for (int j = n - 1; j >= 0; j--) {
    for (int i = 0; i <= j; i++) {
      prixArbre[i][j] = exp(-tauxR*dt)*(p*prixArbre[i][j + 1] + (1 - p)*prixArbre[i + 1][j + 1]);
    }
  }
  return prixArbre[0][0];
}
int main(){
Binomial2 obj = Binomial2(0.25,100.00,60.00,0.02,10,10);
cout<<"prix du put: "<<obj.getPrixPut();
cout<<"prix du call: "<<obj.getPrixCall();
}

/*double payOffCb= calculerPayOffBaisseD( prixS0, ecartType,periodT, prixStrikeK,true);
double payOffCh= calculerPayOffHausseU( prixS0, ecartType,periodT, prixStrikeK,true);
cout<<"payOff baisse:"<<payOffCb<<" ";
cout<<"payOff hausse "<<payOffCh<<" ";*/
/*double priceC = obj.getPrixCall();
cout<<"prix du call: "<<priceC<<"\n";
}*/
