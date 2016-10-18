#include <stdio.h>
#include <math.h>

double f(double);
double dfdx(double);
double newton(double);

int main () {
  double x0 =1.0;
  double solution = newton(x0);
  printf("solution is %f\n", solution);
  return 0;
}

double f(double x) {
  return exp(x) + x;
}

double dfdx(double x) {
  return exp(x) + 1;
}

double newton(double xn){
  double x_n1 = xn - f(xn)/dfdx(xn);
  printf("%f %f\n", xn, x_n1);
  
  if (fabs(x_n1 - xn) < 0.01){
    return x_n1;
  }
  return  newton(x_n1);
}


