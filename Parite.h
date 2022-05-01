

class Parite{
public:
double prixSt;
double prixStrikeK;
double prixCall;
double prixPut;
double tauxR;
long periodT;
public:
Parite(double prixSt,double prixStrikeK,double prixCall,double prixPut,double tauxR,long periodT);
bool isValueOk();
};
