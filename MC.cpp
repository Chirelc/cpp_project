
#include <iostream>
#include <random>
#include <chrono>
#include <tgmath.h>
#include <list>
#include <math.h>
#include<algorithm>
using namespace std;
// ce sont des valeurs fixées arbitrairement mais qui peuvent etre generés via Black and Sholes
//taux sans risque R
const double r=0.02;
//le premier sous jacent généré via s
const double  S_0=100.00;
//la volatilitée
const double ecartType=0.25;
static  double G;
const long periodT=1.00;
const double strikeK=60.00;
//nombre de trajectoirs
const int N=10000;
//const alpha=0.05;
// loie normal centrée reduite généré aléatoirement
double genererNbreLoiNormale(){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  normal_distribution<double> distribution(0.0,1.0);
  G=distribution(generator);
  //cout<<"loie normal: "<<G<<"\n";
  return G ;
}
//periotT doit etre renseigné en jours , à égalment faire en changant d'echelles dt=NbrP/dateM
list<double> simuler_une_trajectoire(long periodT, double r, double ecartType, double nbreLoiNormal){
;
double p[periodT];
p[0]= S_0;
//on calcule la periode 1= p[1]
  for(int i=0;i<periodT; i++){
  p[i+1]=p[i]*exp((r -(pow(ecartType,2)/2 ))*(i+1)+ecartType*sqrt(i+1)*nbreLoiNormal);
  //p[i+1]=p[i]*exp((r -(ecartType/2 ))*(i+1)+ecartType*sqrt(i+1)*nbreLoiNormal);
  }
  list<double> pl (p, (p + (sizeof(p) / sizeof(double)))+1 );
return pl;
}
//sous jacents=> simuler_une_trajectoire ou simuler_N_trajectoire
list<list<double> > simuler_N_trajectoire(int N, long periodT, double r, double ecartType, double nbreLoiNormal){
list<list<double> > res;
for(int i=0;i<N;i++){
  list<double> p (simuler_une_trajectoire( periodT,r, ecartType,nbreLoiNormal));
  list<list<double> >::iterator it= res.begin();
  advance(it,i);
  res.insert(it, p);
  nbreLoiNormal=genererNbreLoiNormale();
}
return res;
}
double calculerPayOff(list<double> x, double strikeK, bool isCall){
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

 list<double> calculerPayOffs(list<list<double> > lx, double strikeK, bool isCall){
  list<double>  payOffs;
  int i=0;
  for(list<list<double> >::iterator it= lx.begin();it!=lx.end();it++){
    list<double> ::iterator it2= payOffs.begin();
    advance(it2,i);
    double p= calculerPayOff(*it,strikeK, isCall);
    payOffs.insert(it2,p);
    i++;
  }
  return payOffs;
}
double calculerMoyennePayOffs(list<list<double> > lx, double strikeK, bool isCall){
 list<double>  payOffs=calculerPayOffs(lx, strikeK, isCall);
 double payOffs_Sum=0.0;
   for(list<double> ::iterator it= payOffs.begin();it!=payOffs.end();it++){
     payOffs_Sum+=*it;
   }
   return payOffs_Sum/payOffs.size();
}

void afficherNTraj(list<list<double> > N_traj){
  for(list<list<double> >::iterator it=N_traj.begin();it!=N_traj.end();it++){
    for(list<double>::iterator it2=it->begin();it2!=it->end();it2++)
      cout <<*it2<<" \n";
  }
}
//on fait l'espérence
// esperence =moyenne
double getPrixCall(long periodT, double r, double ecartType, double strikeK){
  bool isCall=true;
  //on estime N
  double nbreLoiNormal = genererNbreLoiNormale();
  list<list<double> > N_traj (simuler_N_trajectoire(N,periodT,r,ecartType,nbreLoiNormal));
  // cout<<"affichage des trajectoires: "<<" \n";
  //afficherNTraj(N_traj);
  double MPay_Off = calculerMoyennePayOffs(N_traj,strikeK,isCall);
  cout<<"verification Moyenne des payoffs: "<<MPay_Off<<"\n";
  double prixCall = exp(-(r*periodT))*MPay_Off;
  return prixCall;
}
// formule avec l'espérence => moyenne
double getPrixPut(long periodT, double r, double ecartType, double strikeK){
  bool isCall=false;
  //on estime N
  double nbreLoiNormal = genererNbreLoiNormale();
  list<list<double> > N_traj (simuler_N_trajectoire(N,periodT,r,ecartType,nbreLoiNormal));
  double MPay_Off = calculerMoyennePayOffs(N_traj,strikeK,isCall);
  cout<<"verification Moyenne des payoffs: "<<MPay_Off<<"\n";
  double prixPut = exp(-(r*periodT))*MPay_Off;
  return prixPut;
}


/*bool Is ValuAtRisqueOK(){

}*/
//controle moyenne de payoff st-ke(-rt)
int main()
{
 /*int nrolls=10000;  // number of experiments
 int nstars=100;    // maximum number of stars to distribute
unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator (seed);
  normal_distribution<double> distribution(0.0,1.0);

  int *p=new int[100];
  for (int i=0; i<5; ++i) {
      cout <<distribution(generator)<<"\n ";
      cout<< distribution(generator);
  }*/
  // test unitaire des fonctions
/*  double nbreLoiNormal = genererNbreLoiNormale();
list<double> traj (simuler_une_trajectoire( periodT,r, ecartType,nbreLoiNormal));
  for(list<double>::iterator it=traj.begin();it!=traj.end();it++){
      cout <<*it<<" \n";
  }
  list<list<double> > N_traj (simuler_N_trajectoire(N,periodT,r,ecartType,nbreLoiNormal));
  for(list<list<double> >::iterator it=N_traj.begin();it!=N_traj.end();it++){
    for(list<double>::iterator it2=it->begin();it2!=it->end();it2++)
      cout <<*it2<<" \n";
  }
  bool isCall = true;
  double payOff= calculerPayOff(traj,strikeK, isCall);
  cout<<"PayOff= "<<payOff;
  list<double> payOffs = calculerPayOffs(N_traj,strikeK,isCall);
    cout<<"list de payOffs:";
    for(list<double>::iterator it=payOffs.begin();it!=payOffs.end();it++){
      cout<<" "<<*it<<" \n";
    }
  double MPay_Off = calculerMoyennePayOffs(N_traj,strikeK,isCall);
  cout<<"moyenne de payOffs= "<<MPay_Off;*/

double prixCall = getPrixCall(periodT, r,ecartType, strikeK);
double prixPut=getPrixPut(periodT,r,ecartType,strikeK);
cout<<"prix du call"<<prixCall<<"\n" ;
cout<<"prix du put "<<prixPut<<"\n";
double controlValuePC=prixCall-prixPut;
cout<<"valeur de control call-put: "<< controlValuePC<<"\n";
// faire une fonction pour ces valeurs de control renvoyant un bool formule de parité


}
