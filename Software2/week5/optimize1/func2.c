#include <math.h>
#include <stdio.h>

typedef struct {
  int id;       // id
  double rm;    // number of rooms
  double price; // house price
} House;

int f_dimension() { return 2; }

double f_value(const double x[], House data[1000]) {
  double E = 0;
  for (int i = 0; i < 500; i++) {
    E += pow(data[i].price - (x[0] * data[i].rm + x[1]), 2);
  }
  return E;
}

void f_gradient(const double x[], double g[], House data[1000]) {
  int i;
  g[0] = 0;
  g[1] = 0;
  for (i = 0; i < 500; i++) {
    g[0] -= 2 * (data[i].price - x[0] * data[i].rm - x[1]) * data[i].rm;
    g[1] -= 2 * (data[i].price - x[0] * data[i].rm - x[1]);
  }
}
