
class BandS{
private :
  double prixStrikeK;
  double tauxR;
  double ecartType;
  double  periodT;
  double prixSt;
  double n;
public:
BandS(double n ,double prixSt,double ecartType, double periodT, double tauxR, double prixStrikeK);
double calculerD1( double dividende);
double calculerD2(double dividende);
double calculerD1();
double calculerD2();
double calculerLoiNormale(double var);
double getPrixCall( double dividende);
double getPrixPut( double dividende);
double getPrixCall();
double getPrixPut();
double calculerLoiNormaleNonCummule(double var);
double getSensibiliteDelta(bool isCall);
double getSensibiliteGamma();
double getSensibiliteVega();
double getSensibiliteRho(bool isCall);
double getSensibiliteTheta(bool isCall);
double getSensibiliteDelta(bool isCall,double dividende);
double getSensibiliteGamma(double dividende);
double getSensibiliteVega(double dividende);
double getSensibiliteRho(bool isCall,double dividende);
double getSensibiliteTheta(bool isCall,double dividende);
bool getParite();
bool getParite(double dividende);
};
