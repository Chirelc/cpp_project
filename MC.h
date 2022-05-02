
using namespace std;
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
double calculEcartType(list<list<double> > N_traj,bool isCall);
bool isInterval_de_confiance_5prct(double val,list<list<double> > N_traj,bool isCall);
};
