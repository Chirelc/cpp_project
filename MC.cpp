#include <iostream>
#include <random>
#include <chrono>
#include <tgmath.h>
#include <list>
#include <math.h>
#include<algorithm>
#include <cstdlib>
#include"MC.h"
using namespace std;
MC::MC(double r,double S_0,double ecartType,double strikeK, int N , long periodT){
  this->r=r;
  this->S_0=S_0;
  this->ecartType=ecartType;
  this->strikeK=strikeK;
  this->N=N;
  this->periodT=periodT;
}
double MC::genererNbreLoiNormale(){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  normal_distribution<double> distribution(0.0,1.0);
  double G=distribution(generator);
  return G ;
}
list<double> MC::simuler_une_trajectoire(double nbreLoiNormal){
double p[periodT];
p[0]= S_0;
  for(int i=0;i<periodT; i++){
  p[i+1]=p[i]*exp((r -(pow(ecartType,2)/2 ))*(i+1)+ecartType*sqrt(i+1)*nbreLoiNormal);
  }
  list<double> pl (p, (p + (sizeof(p) / sizeof(double)))+1 );
return pl;
}
list<list<double> > MC::simuler_N_trajectoire(double nbreLoiNormal){
list<list<double> > res;
for(int i=0;i<N;i++){
  list<double> p (simuler_une_trajectoire( nbreLoiNormal));
  list<list<double> >::iterator it= res.begin();
  advance(it,i);
  res.insert(it, p);
  nbreLoiNormal=genererNbreLoiNormale();
}
return res;
}
double MC::calculerPayOff(list<double> x, bool isCall){
  double payOff;
  if(isCall){
    list<double>::iterator it=x.end();
    it--;
    payOff=max(0.0,*it-strikeK);
  }else{
    list<double>::iterator it=x.end();
    it--;
    payOff=max(0.0,strikeK-*it);
   }
   return payOff;
}

 list<double> MC::calculerPayOffs(list<list<double> > lx, bool isCall){
  list<double>  payOffs;
  int i=0;
  for(list<list<double> >::iterator it= lx.begin();it!=lx.end();it++){
    list<double> ::iterator it2= payOffs.begin();
    advance(it2,i);
    double p= calculerPayOff(*it,isCall);
    payOffs.insert(it2,p);
    i++;
  }
  return payOffs;
}
double MC::calculerMoyennePayOffs(list<list<double> > lx, bool isCall){
 list<double>  payOffs=calculerPayOffs(lx,isCall);
 double payOffs_Sum=0.0;
   for(list<double> ::iterator it= payOffs.begin();it!=payOffs.end();it++){
     payOffs_Sum+=*it;
   }
   return payOffs_Sum/payOffs.size();
}

void MC::afficherNTraj(list<list<double> > N_traj){
  for(list<list<double> >::iterator it=N_traj.begin();it!=N_traj.end();it++){
    for(list<double>::iterator it2=it->begin();it2!=it->end();it2++)
      cout <<*it2<<" \n";
  }
}

double MC::getPrixCall(){
  bool isCall=true;
  //on estime N
  double nbreLoiNormal = genererNbreLoiNormale();
  list<list<double> > N_traj (simuler_N_trajectoire(nbreLoiNormal));
  // cout<<"affichage des trajectoires: "<<" \n";
  //afficherNTraj(N_traj);
  double MPay_Off = calculerMoyennePayOffs(N_traj,isCall);
  double prixCall = exp(-(r*periodT))*MPay_Off;
  isInterval_de_confiance_5prct(prixCall, N_traj, isCall);
  return prixCall;
}

double MC::getPrixPut(){
  bool isCall=false;
  double nbreLoiNormal = genererNbreLoiNormale();
  list<list<double> > N_traj (simuler_N_trajectoire(nbreLoiNormal));
  double MPay_Off = calculerMoyennePayOffs(N_traj,isCall);
  double prixPut = exp(-(r*periodT))*MPay_Off;
  isInterval_de_confiance_5prct(prixPut, N_traj, isCall);
  return prixPut;
}
double MC::calculEcartType(list<list<double> > N_traj,bool isCall){
list<double> listPO = calculerPayOffs(N_traj, isCall);
double moyenPO=calculerMoyennePayOffs( N_traj,isCall );
double sumX=0;
list <double> ::iterator it=listPO.begin();
for(int i=0;i<listPO.size();i++){
    advance(it,i);
    sumX+=pow(*it-moyenPO,2);
}
return sqrt(sumX/listPO.size());
}
bool MC::isInterval_de_confiance_5prct(double val,list<list<double> > N_traj,bool isCall ){
    double born1;
    born1=val+1.96*calculEcartType(N_traj,isCall)/sqrt(N);
    double born2;
    born2=val-1.96*calculEcartType(N_traj,isCall)/sqrt(N);;
    double c=calculEcartType(N_traj,isCall )/sqrt(N);
string type;
if(isCall){
type=" du Call: ";
}else{
type=" du Put: ";
}
cout<<"borne inférieur"<<type<<born2<<" borne supérieur"<<type<<born1<<"\n";
  if(abs(born1-born2)<=(1.96*c)){
    return true;
  cout<<"on a bien un interval de confiance à 5 % "<<"\n";
  }
  return false;
}
