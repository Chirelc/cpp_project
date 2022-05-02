#include"Binomial.h"
Binomial::Binomial(double ecartType,double prixS0,double prixStrikeK,double tauxR,long periodT,long n ){
  this->ecartType=ecartType;
  this->prixS0=prixS0;
  this->prixStrikeK=prixStrikeK;
  this->tauxR=tauxR;
  this->periodT=periodT;
  this->n=n;
}

double Binomial::calculerProbabiliteHausseU(){
double dt=periodT/n;
double c2=sqrt(dt);
return exp(ecartType*c2);
}
double Binomial::calculerProbabiliteBaisseD(){
  double dt=periodT/n;
  double c2=sqrt(dt);
  return  exp(-ecartType*c2);
}
vector<vector<double> > Binomial::calculerPrixSt(){
vector<vector<double> >  prixSt(n + 1, vector<double>(n + 1, 0));
double d=calculerProbabiliteBaisseD();
double u=calculerProbabiliteHausseU();
for (int j = 0; j <= n; j++) {
       for (int i = 0; i <= j; i++) {
           prixSt[i][j] = prixS0*pow(u, j - i)*pow(d, i);
       }
   }

return prixSt;
}
vector<vector<double> > Binomial::calculerPayOffs(bool isCall){
vector<vector<double> >  valeurSt= calculerPrixSt();
vector<vector<double> >  prixArbre(n + 1, vector<double>(n + 1, 0));
 for (int i = 0; i <= n; i++) {
   if(isCall){
   prixArbre[i][n]=max(valeurSt[i][n] - prixStrikeK, 0.0);
 }if(!isCall){
   prixArbre[i][n]=max(prixStrikeK-valeurSt[i][n], 0.0);
 }

 }
  return prixArbre;
}

double Binomial::getPrixCall(){
double dt= periodT/n;
double Call;
double  p= (exp(tauxR*dt)-calculerProbabiliteBaisseD())/(calculerProbabiliteHausseU()-calculerProbabiliteBaisseD());
vector<vector<double > > prixArbre = calculerPayOffs(true);
for (int j = n - 1; j >= 0; j--) {
  for (int i = 0; i <= j; i++) {
    prixArbre[i][j] = exp(-tauxR*dt)*(p*prixArbre[i][j + 1] + (1 - p)*prixArbre[i + 1][j + 1]);
    }
  }
  return prixArbre[0][0];
}

double Binomial::getPrixPut(){
  double dt= periodT/n;
  double  p= (exp(tauxR*dt)-calculerProbabiliteBaisseD())/(calculerProbabiliteHausseU()-calculerProbabiliteBaisseD());
  vector<vector<double > > prixArbre = calculerPayOffs(false);
  for (int j = n - 1; j >= 0; j--) {
    for (int i = 0; i <= j; i++) {
      prixArbre[i][j] = exp(-tauxR*dt)*(p*prixArbre[i][j + 1] + (1 - p)*prixArbre[i + 1][j + 1]);
    }
  }

  return prixArbre[0][0];
}
