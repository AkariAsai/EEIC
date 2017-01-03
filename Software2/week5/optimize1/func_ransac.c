#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  int id;       // id
  double rm;    // number of rooms
  double price; // house price
} House;

unsigned int xorshift() {
  static unsigned int x = 1;
  static unsigned int y = 2;
  static unsigned int z = 3;
  static unsigned int w = 4;
  unsigned int t;

  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

double random_double() { return xorshift() * 1.0 / 4294967295.0; };

int f_dimension() { return 2; }

double f_value(const double x[], House data[1000]) {
  srand((unsigned)time(NULL));
  double E = 0;
  for (int i = 0; i < 500; i++) {
    if (random_double() < 0.02) {
      E += pow(data[i].price - (x[0] * data[i].rm + x[1]), 2);
    }
  }
  return E;
}

void f_gradient(const double x[], double g[], House data[1000]) {
  srand((unsigned)time(NULL));
  int i;
  g[0] = 0;
  g[1] = 0;
  for (i = 0; i < 500; i++) {
    if (random_double() < 0.02) {
      g[0] -= 2 * (data[i].price - x[0] * data[i].rm - x[1]) * data[i].rm;
      g[1] -= 2 * (data[i].price - x[0] * data[i].rm - x[1]);
    }
  }
}
