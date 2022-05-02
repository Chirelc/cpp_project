
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
    //this->mu=mu;
    this->ecartType=ecartType;
    this->periodT=periodT;
    this->tauxR=tauxR;
    this->prixStrikeK=prixStrikeK;
    this->prixSt=prixSt;
    //this->S_0=S_0;
  }
  double BandS::calculerLoiNormaleNonCummule( double x){
      return (1.0/(pow(2*3.14,0.5)))*exp(-0.5*x*x);
  }


  /*list<double> BandS::simulation_trajectoire_mvt_brownien(){
  double deltaT=periodT/n;
  double v2=ecartType*sqrt(deltaT);
  double v= mu*deltaT;
  list<double> list_w;
  list<double> list_st;
  list<double> ::iterator it= list_w.begin();
  list<double> ::iterator it2= list_st.begin();
  double sumW=0;
  for(double i=0.0;i<periodT;i+=deltaT){
  advance(it,i);
  advance(it2,i);
  double W =calculerLoiNormaleNonCummule(v,v2);
  sumW+=W;
  list_w.insert(it,sumW);
  list_st.insert (it2,S_0*exp(sumW));
}*/
  /*list<double> ::iterator it3= list_st.begin();
  double st;
  for(int i=0;i<t;i++){
  advance(it3,i);
  }
  st=*it3;
  this->list_St=list_st;
  return list_st;
}*/
double BandS::calculerD1(){
return (log(prixSt/prixStrikeK)+(tauxR+(pow(ecartType,2.00)/2)*periodT))/(ecartType*sqrt(periodT));
}

double BandS::calculerD1(double dividende){
  return (log(prixSt/prixStrikeK)+(tauxR - dividende +(pow(ecartType,2.00)/2)*periodT))/(ecartType*sqrt(periodT));
}
/*double calculerLoiNormaleD1(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  double d1= calculerD1( prixSt, ecartType, periodT, tauxR, prixStrikeK);
  normal_distribution<double> distribution(0.0,d1);
  double N = generator(distribution);
  return N;
}*/
/*double BandS::calculerLoiNormaleD2(double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  double d2= calculerD2( prixSt, ecartType, periodT, tauxR, prixStrikeK);
  normal_distribution<double> distribution(0.0,d2);
  double N = generator(distribution);
  return N;
}*/

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
/*list<double> BandS::getSt(){
  return list_St;
}*/

/*int main(){
  double prixStrikeK=60;
  double tauxR=0.02;
  double ecartType=0.25;
  double periodT=1;
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

  double n=1;
  bool parite ;

  double prixSt=100;
  double spotTime;

  BandS bands = BandS(1,100,0.25, 1,0.02,60.00);
  string isDiv;
    cout<<"y'a t-il un dividende ? (oui ou non) "<<"\n";
    cin>>isDiv;
    double dividende;
    if(isDiv=="oui"){
    dividende=0.02;
  }*/
  /*list_st=bands.simulation_trajectoire_mvt_brownien();
  list<double> ::iterator it= list_st.begin();
  double deltaT=periodT-(spotTime/n);
  for(int i=0;i<deltaT;i++){
    advance(it,i);
    prixSt=*it;
  }*/
  /*  if(isDiv=="oui"){
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
    parite = bands.getParite(dividende);
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
    parite = bands.getParite();
  }
  string affG;
  cout<<"Voici le prix du Call: "<<Call<<" et voici le prix du Put: "<<Put<<"\n";
  cout<<"Souhaitez-vous l'affichage des Grecques?(oui ou non)"<<"\n";
  cin>>affG;
  if(affG=="oui"){
  cout<<"Voici les grecques: "<<"\n";
  cout<<"L'indicateur Delta: "<<"\n";
  cout<<"Delta pour un put: "<<deltaP<<" Delta pour un Call: "<<deltaC<<"\n";
  cout<<"L'indicateur Gamma: "<<gamma<<"\n";
  cout<<"l'indicateur Vega: "<<vega<<"\n";
  cout<<"l'indicateur Theta:"<<"\n";
  cout<<"Theta pour un Put: "<<thetaP<<" Theta pour un Call: "<<thetaC<<"\n";
  cout<<"l'indicateur Rho: "<<"\n";
  cout<<"Rho pour un Put: "<<rhoP<<" Rho pour un Call: "<<rhoC<<"\n";
  }
  cout<<"Vérification de la validité des valeurs calculés par la librairie: "<<"\n";
  if(parite==true){
    cout<<"les bornes sur les prix sont bien respectés "<<"\n";
  }else{
    cout<<"les bornes sur les prix  ne sont pas respectés "<<"\n";
    cout<<"Il y'a une erreur de calcule pour une valeur  "<<"\n";
  }
}*/
