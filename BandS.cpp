
#include "BandS.h"
  BandS::BandS(double mu,double n,double prixSt, double ecartType, long periodT, double tauxR, double prixStrikeK){
    this->n=n;
    this->mu=mu;
    this->ecartType=ecartType;
    this->periodT=periodT;
    this->tauxR=tauxR;
    this->prixStrikeK=prixStrikeK;
    this->prixSt=prixSt;
    //this->S_0=S_0;
  }
  double BandS::calculerLoiNormaleNonCummule(double a, double var){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution(a,var);
    double G=distribution(generator);
    //cout<<"ln: "<<G;
    return G ;
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
  double d1=calculerD1(prixSt);
  if(isCall){
    return calculerLoiNormale(d1);
  }else{
    return calculerLoiNormale(d1) - 1;
  }
}

double BandS::getSensibiliteDelta(bool isCall,double dividende){
    double d1=calculerD1(dividende);
  if(isCall){
    return calculerLoiNormale(d1);
  }else{
    return calculerLoiNormale(d1) - 1;
  }
}

double BandS::getSensibiliteGamma(){
  double d1=calculerD1();
  return calculerLoiNormaleNonCummule(0.0,d1)/(prixSt*ecartType*sqrt(periodT));

}
double BandS::getSensibiliteGamma(double dividende){
  double d1=calculerD1(dividende);
  return calculerLoiNormaleNonCummule(0.0,d1)/(prixSt*ecartType*sqrt(periodT));

}
double BandS::getSensibiliteVega(){
  double d1=calculerD1();
  return prixSt*calculerLoiNormaleNonCummule(0.0,d1)*sqrt(periodT);
}

double BandS::getSensibiliteVega(double dividende){
  double d1=calculerD1(dividende);
  return prixSt*calculerLoiNormaleNonCummule(0.0,d1)*sqrt(periodT);
}
double BandS::getSensibiliteTheta(bool isCall){
  double d1=calculerD1();
  double d2=calculerD2();
  if(isCall){
      return (prixSt*calculerLoiNormaleNonCummule(0.0,d1)*ecartType)/(2*sqrt(periodT))+tauxR*prixStrikeK*exp(-tauxR*periodT)*calculerLoiNormale(d2);
  }else{
  return -(prixSt*calculerLoiNormaleNonCummule(0.0,d1)*ecartType)/(2*sqrt(periodT))-tauxR*prixStrikeK*exp(-tauxR*periodT)*calculerLoiNormale(d2);
  }
}
double BandS::getSensibiliteTheta(bool isCall,double dividende ){
  double d1=calculerD1(dividende);
  double d2=calculerD2(dividende);
  if(isCall){
      return (prixSt*calculerLoiNormaleNonCummule(0.0,d1)*ecartType)/(2*sqrt(periodT))+tauxR*prixStrikeK*exp(-tauxR*periodT)*calculerLoiNormale(d2);
  }else{
  return -(prixSt*calculerLoiNormaleNonCummule(0.0,d1)*ecartType)/(2*sqrt(periodT))-tauxR*prixStrikeK*exp(-tauxR*periodT)*calculerLoiNormale(d2);
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
Parite p= Parite(prixSt,prixStrikeK,getPrixCall(), getPrixPut(),tauxR,periodT);
bool res;
res=p.isValueOk();
return res;
}

bool BandS::getParite(double dividende){
Parite p= Parite(prixSt,prixStrikeK,getPrixCall(dividende), getPrixPut(dividende),tauxR,periodT);
bool res;
res=p.isValueOk();
return res;
}
/*list<double> BandS::getSt(){
  return list_St;
}*/

/*int main(){
double prixSt=100.00;
double prixStrikeK=60.00;
double tauxR=0.02;
double ecartType=0.25;
long periodT=1;
double  n=0.01;
double mu=0.03;
BandS obj = BandS(mu,n,ecartType,periodT,tauxR,prixStrikeK);
list<double> list_st=obj.simulation_trajectoire_mvt_brownien();
for(list<double> ::iterator it= list_st.begin();it!=list_st.end();it++){
  double call=obj.getPrixCall(*it);
  double put= obj.getPrixPut(*it);
  cout<<"put :"<<put;
  cout<<"call :"<<call;
}}*/
