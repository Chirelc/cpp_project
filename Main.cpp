#include <iostream>
#include <string.h>
#include <list>
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
getline(cin, methode);
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
  cout<<"rentrer les valeurs suivantes: "<<"\n";
  cout<<"rentrer la durée de l’échéance de l'option: "<<"\n";
  cin>>periodT;
  cout<<"entrer le prix du sous-jacent à t=0: "<<"\n";
  cin>>S_0;
  cout<<"entrer le  nombre de generation de trajectoires voulu: "<<"\n";
  cin>>N;
  cout<<"entrer le taux sans risque de l'option à appliquer: "<<"\n";
  cin>>r;
  cout<<"entrer la prime de l'option: "<<"\n";
  cin>>strikeK;
  cout<<"entrer la volatilitée de l'option: "<<"\n";
  cin>>ecartType;
  MC mc = MC(r,S_0,ecartType, strikeK, N,periodT);
  double Call=mc.getPrixCall();
  double Put=mc.getPrixPut();
  cout<<"voici le prix du Call: "<<Call<<"\n";
  cout<<"voici le prix du Put: "<<Put<<"\n";
}
if(methode=="Black and Sholes"){
  double prixStrikeK;
  double tauxR;
  double ecartType;
  long periodT;
  double Call;
  double Put;
  double deltaC;
  double deltaP;
  double gamma;
  double vega;
  double thetaC;
  double thetaP;
  double rhoP;
  double rhoC;
  //double S_0;
  double mu;
  double n;
  bool parite ;
  list<double> list_st;
  double prixSt;
  double spotTime;
  /*
  list<double> list_st;
  double prixStrikeK;
  double tauxR;
  double ecartType;
  long periodT;
  double S_0;
  list<double> list_St;
  double n;
  double mu;
public:
BandS(double mu,double n ,double ecartType, long periodT, double tauxR, double prixStrikeK);*/
  cout<<"rentrer les valeurs suivantes:"<<"\n";
  cout<<"entrer le prix de l'exercice: "<<"\n";
  cin>>prixStrikeK;
  cout<<"entrer le taux sans risque de l'option :"<<"\n";
  cin>>tauxR;
  cout<<"entrer la date d'échéance de l'option (en année)"<<"\n";
  cin>>periodT;
  cout<<"entrer la volatilité du sous jacent: "<<"\n";
  cin>>ecartType;
  cout<<"entrer le nombre de périodes: "<<"\n";
  cin>>n;
  cout<<"entrer le drift du mouvement brownien mu: "<<"\n";
  cin>>mu;
  /*cout<<"entrer la valeur du sous jacent au temp 0:"<<"\n";
  cin>>S_0;*/
  /*cout<<"entrer l'age de l'option: "<<"\n";
  cin>>spotTime;*/
  cout<<"entrer le spot price: "<<"\n";
  cin>>prixSt;
  BandS bands = BandS(mu,n,prixSt,ecartType, periodT,tauxR,prixStrikeK);
  string isDiv;
    cout<<"y'a t-il un dividende ? (oui ou non) "<<"\n";
    cin>>isDiv;
    double dividende;
    if(isDiv=="oui"){
    cout<<"entrer le dividende"<<"\n";
    cin>>dividende;
  }
  /*list_st=bands.simulation_trajectoire_mvt_brownien();
  list<double> ::iterator it= list_st.begin();
  double deltaT=periodT-(spotTime/n);
  for(int i=0;i<deltaT;i++){
    advance(it,i);
    prixSt=*it;
  }*/
    if(isDiv=="oui"){
    Call= bands.getPrixCall(dividende);
    Put=bands.getPrixPut(dividende);
    deltaC=bands.getSensibiliteDelta(true,dividende);
    deltaP=bands.getSensibiliteDelta(false,dividende);
    gamma=bands.getSensibiliteGamma(dividende);
    vega=bands.getSensibiliteVega(dividende);
    thetaC=bands.getSensibiliteTheta(true,dividende);
    thetaP=bands.getSensibiliteTheta(false,dividende);
    rhoP=bands.getSensibiliteRho(false,dividende);
    rhoC=bands.getSensibiliteRho(true,dividende);
    }else{
    Call= bands.getPrixCall();
    Put=bands.getPrixPut();
    deltaC=bands.getSensibiliteDelta(true);
    deltaP=bands.getSensibiliteDelta(false);
    gamma=bands.getSensibiliteGamma();
    vega=bands.getSensibiliteVega();
    thetaC=bands.getSensibiliteTheta(true);
    thetaP=bands.getSensibiliteTheta(false);
    rhoP=bands.getSensibiliteRho(false);
    rhoC=bands.getSensibiliteRho(true);
    cout<<"voici le prix du Call: "<<Call<<" et voici le prix du Put: "<<Put<<"\n";
    parite = bands.getParite();
  }

  cout<<"voici les greques: "<<"\n";
  cout<<"l'indicateur Delta: qui détermine la sensibilitée du prix à une variation du sous-jacent: "<<"\n";
  cout<<"Delta pour un put: "<<deltaP<<"\n";
  cout<<"Delta pour un Call: "<<deltaC<<"\n";
  cout<<"l'indicateur Gamma: qui détermine l'accéleration du prix à une variation de sous-jacent: "<<"\n";
  cout<<"Gamma: "<<gamma<<"\n";
  cout<<"l'indicateur Vega qui détermine la variation de la volatilité du sous-jacent: "<<"\n";
  cout<<"Vega: "<<vega<<"\n";
  cout<<"l'indicateur Theta qui détermine la sensibilitée du prix du sous-jacent lors de la variation de la maturitée de l'option: "<<"\n";
  cout<<"Theta pour un Put: "<<thetaP<<"\n";
  cout<<"Theta pour un Call: "<<thetaC<<"\n";
  cout<<"l'indicateur Rho qui détermine la sensibilitée du prix du sous-jacent à une variation du taux sans risque "<<"\n";
  cout<<"Rho pour un Put: "<<rhoP<<"\n";
  cout<<"Rho pour un Call: "<<rhoC<<"\n";
  cout<<"Vérification de la validitée des valeurs calculés par la librairie: "<<"\n";
  cout<<"la vérification à lieu uniquement pour le call et put à maturité: "<<"\n";
  if(parite){
    cout<<"les bornes sur les prix sont bien respectés "<<"\n";
  }else{
    cout<<"les bornes sur les prix  ne sont pas respectés "<<"\n";
    cout<<"il y'a une erreur de calcule pour une valeur  "<<"\n";
  }
}
}
