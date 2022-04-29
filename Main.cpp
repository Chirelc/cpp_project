#include <iostream>
#include <string.h>
#include "Binomial.cpp"
#include "BandS.cpp"
#include "MC.cpp"
using namespace std;
int main(){
string methode;
cout<<"Choisisez la méhode de pricing:"<<"\n";
cout<<"Monte Carlos"<<"\n";
cout<<"Binomial"<<"\n";
cout<<"Black and Sholes"<<"\n";
cin>>methode;
cout<<"vous avez choisis la méthode de:"<<methode<<"\n";
if(methode=="Binomial"){
  double ecartType;
  double prixS0;
  double prixStrikeK;
  double tauxR;
  long periodT;
  long n ;
  cout<<"rentrer les valeurs suivantes:"<<"\n";
  cout<<"le cours de l'action en t=0"<<"\n";
  cin>>prixS0;
  cout<<"Entrer la durée de l’échéance de l'option: "<<"\n";
  cin>>periodT;
  cout<<"entrer le nombre de périodes: "<<"\n";
  cin>>n;
  cout<<"le taux sans risque:"<<"\n";
  cin>>tauxR;
  cout<<"prix fixé du sous jacent à l'échéance :"<<"\n";
  cin>>prixStrikeK;
  cout<<"entrer la volatilité du sous-jacent"<<"\n";
  cin>>ecartType;
  Binomial bin = Binomial(ecartType,prixS0,prixStrikeK,tauxR,periodT,n);
  double Call=bin.getPrixCall();
  double Put=bin.getPrixPut();
  cout<<"voici le prix du Call:"<<Call<<"\n";
  cout<<"voici le prix du Put: "<<Put<<"\n";
}
if(methode == "Monte Carlos"){
  double r;
  double S_0;
  double ecartType;
  double strikeK;
  int N;
  long periodT;
  cout<<"rentrer les valeurs suivantes:"<<"\n";
  cout<<"rentrer la durée de l’échéance de l'option "<<"\n"
  cin>>periodT;
  cout<<"entrer le prix du sous-jacent à t=0"<<"\n";
  cin>>S_0;
  cout<<"entrer le  nombre de generation de trajectoires voulu "<<"\n";
  cin>>N;
  cout<<"entrer le taux sans risque de l'option à appliquer: "<<"\n";
  cin>>r;
  cout<<"entrer la prime de l'option :"<<"\n";
  cin>>strikeK;
  cout<<"entrer la volatilitée de l'option:"<<"\n";
  cin>>ecartType;
  MC mc = MC(r,S_0,ecartType, strikeK, N,periodT);
  double Call=mc.getPrixCall();
  double Put=mc.getPrixPut()
  cout<<"voici le prix du Call:"<<Call<<"\n";
  cout<<"voici le prix du Put: "<<Put<<"\n";
}
if(methode=="Black and Sholes"){
  double prixStrikeK;
  double tauxR;
  double ecartType;
  long periodT;
  //double S_0;
  double prixSt;
  cout<<"rentrer les valeurs suivantes:"<<"\n";
  cout<<"entrer le prix de l'exercice: "<<"\n";
  cin>>prixStrikeK;
  cout>>"entrer le taux sans risque de l'option :"<<"\n";
  cin>>tauxR;
  cout<<"entrer la date d'échéance de l'option (en année)"<<"\n";
  cin>>periodT;
  cout<<"entrer la valeur du sous jacent au temp t:"<<"\n";
  cin>>prixSt;
  //cout<<"entrer la valeur du sous jacent au temp 0:"<<"\n";
  //cin>>S_0;
  BandS bands = BandS(prixSt,ecartType, periodT,tauxR,prixStrikeK);
  bool isDiv;
  cout<<"y'a t-il un dividende ? (true ou false) "<<"\n";
  cin>>isDiv;
  if(isDiv){
  double dividende
  cout<<"entrer le dividende"<<"\n";
  cin>>dividende;
  double Call= bands.getPrixCall(dividende);
  double Put=bands.getPrixPut(dividende);
  double deltaC=bands.getSensibiliteDelta(true,dividende);
  double deltaP=bands.getSensibiliteDelta(false,dividende);
  double gamma=bands.getSensibiliteGamma(dividende);
  double vega=bands.getSensibiliteVega(dividende);
  double thetaC=bands.getSensibiliteTheta(true,dividende);
  double thetaP=bands.getSensibiliteTheta(false,dividende);
  double rhoP=bands.getSensibiliteRho(false,dividende);
  double rhoC=bands.getSensibiliteRho(true,dividende);
  }else{
  double Call= bands.getPrixCall();
  double Put=bands.getPrixPut();
  double deltaC=bands.getSensibiliteDelta(true);
  double deltaP=bands.getSensibiliteDelta(false);
  double gamma=bands.getSensibiliteGamma();
  double vega=bands.getSensibiliteVega();
  double thetaC=bands.getSensibiliteTheta(true);
  double thetaP=bands.getSensibiliteTheta(false);
  double rhoP=bands.getSensibiliteRho(false);
  double rhoC=bands.getSensibiliteRho(true);
  }
  cout<< "voici le prix du Call: "<<Call<<"\n";
  cout<<"voici le prix du Put: "<<Put<<"\n";
  cout<<"voici les grecs: "<<"\n";
  cout<<"l'indicateur Delta: qui détermine la sensibilitée du prix à une variation du sous-jacent: "<<"\n";
  cout<<"Delta pour un put: "<<deltaP<<"\n";
  cout<<"Delta pour un Call: "<<deltaC<<"\n";
  cout<<"l'indicateur Gamma: qui détermine l'accéleration du prix à une variation de sous-jacent: "<<"\n";
  cout<<"Gamma: "<<gamma<<"\n";
  cout<<"l'indicateur Vega qui détermine la variation de la volatilité du sous-jacent: "<<"\n";
  cout<<"Vega: "<<vega<<"\n";
  cout<<"l'indicateur Theta qui détermine la sensibilité du prix du sous-jacent lors de la variation de la maturitée de l'option: "<<"\n";
  cout<<"Theta pour un Put: "<<thetaP<<"\n";
  cout<<"Theta pour un Call: "<<thetaC<<"\n";
  cout<<"l'indicateur Rho qui determine la sensibilité du prix du sous-jacent à une variation du taux sans risque "<<"\n";
  cout<<"Rho pour un Put: "<<rhoP<<"\n";
  cout<<"Rho pour un Call: "<<rhoC<<"\n";

}
}
