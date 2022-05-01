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
return exp(ecartType*sqrt(periodT/n));
}
double Binomial::calculerProbabiliteBaisseD(){
  return exp(-(ecartType*sqrt(periodT/n)));
}
// j'ai ajouté prixStrike
//ajout isCall or pUT
vector<vector<double> > Binomial::calculerPrixSt(){
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
vector<vector<double> > Binomial::calculerPayOffs(bool isCall){
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
double Binomial::getPrixCall(){
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

double Binomial::getPrixPut(){
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
/*int main(){
Binomial2 obj = Binomial2(0.25,100.00,60.00,0.02,10,10);
cout<<"prix du put: "<<obj.getPrixPut();
cout<<"prix du call: "<<obj.getPrixCall();
}*/

/*double payOffCb= calculerPayOffBaisseD( prixS0, ecartType,periodT, prixStrikeK,true);
double payOffCh= calculerPayOffHausseU( prixS0, ecartType,periodT, prixStrikeK,true);
cout<<"payOff baisse:"<<payOffCb<<" ";
cout<<"payOff hausse "<<payOffCh<<" ";*/
/*double priceC = obj.getPrixCall();
cout<<"prix du call: "<<priceC<<"\n";
}*/
