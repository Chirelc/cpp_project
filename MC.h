
using namespace std;
// ce sont des valeurs fixées arbitrairement mais qui peuvent etre generés via Black and Sholes
//taux sans risque R
/*const double r=0.02;
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
// loie normal centrée reduite généré aléatoirement*/
class MC{
private:
  double r;
  double S_0;
  double ecartType;
  double strikeK;
  int N;
  long periodT;
public:
MC(double r,double S_0,double ecartType,double strikeK, int N, long periodT);
double genererNbreLoiNormale();
list<double> simuler_une_trajectoire(double nbreLoiNormal);
list<list<double> > simuler_N_trajectoire(double nbreLoiNormal);
double calculerPayOff(list<double> x,bool isCall);
list<double>  calculerPayOffs(list<list<double> > lx, bool isCall);
double calculerMoyennePayOffs(list<list<double> > lx, bool isCall);
void afficherNTraj(list<list<double> > N_traj);
double getPrixCall();
double getPrixPut();
bool isInterval_de_confiance_5prct(double val,list<list<double> > N_traj,bool isCall);
};
