#include <iostream>
#include <string>
#include <random>
using namespace std;

int main ()
{
default_random_engine generator;
normal_distribution<double> distribution(0,1);
int p[10]={};
for (int i=0; i<10000; ++i) {
  double number = distribution(generator);
  if ((number>=0.0)&&(number<10.0)) ++p[int(number)];
}

cout << "normal_distribution (0,1):";
for (int i=0; i<10; ++i) {
  cout << string(p[i]);
}
}
