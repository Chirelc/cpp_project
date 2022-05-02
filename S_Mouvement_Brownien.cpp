#include <iostream>
#include <random>
#include <chrono>
#include <tgmath.h>
#include <list>
#include <math.h>
#include<algorithm>
#include <cstdlib>

double prixStrikeK;
double tauxR;
double ecartType;
double  periodT;
double n;
double mu;
double prixS0;
// ce code sort un tableau a t=0 à t=periodT
//avec pour chaque t, un st, suivant un mouvement brownien
list<double> simulation_trajectoire_mvt_brownien(){
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
}
list<double> ::iterator it3= list_st.begin();
double st;
for(int i=0;i<t;i++){
advance(it3,i);
}
st=*it3;
this->list_St=list_st;
return list_st;
}
