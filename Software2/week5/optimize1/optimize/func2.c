#include <math.h>
#include <stdio.h>

typedef struct {
  char *loc;   // location name
  double alt;  // altitude (km)
  double temp; // temperature (centigrade)
} Sample;

const Sample data[] = {
    {"Nozawa-onsen", 0.576, 22.3}, {"Iiyama", 0.313, 23.3},
    {"Nagano", 0.4182, 23.8},      {"Oomachi", 0.784, 21.1},
    {"Sugadaira", 1.253, 18.5},    {"Karuizawa", 0.9991, 19.5},
    {"Matsumoto", 0.610, 23.6},    {"Nagawa", 1.068, 19.7},
    {"Suwa", 0.760, 22.7},         {"Nobeyama", 1.350, 18.4},
    {"Ina", 0.633, 22.7},          {"Nagiso", 0.560, 22.3},
    {"Iida", 0.5164, 23.9},        {"Minami-shinano", 0.407, 23.5}};

const int nsamples = sizeof(data) / sizeof(data[0]);

int f_dimension() { return 2; }

double f_value(const double x[]) {
  double E = 0;
  for (int i = 0; i < 14; i++) {
    E += pow(data[i].temp - (x[0] * data[i].alt + x[1]), 2);
  }
  return E;
}

void f_gradient(const double x[], double g[]) {
  printf("Hello");
  int i;
  g[0] = 0;
  g[1] = 0;
  for (i = 0; i < nsamples; i++) {
    g[0] -= 2 * (data[i].temp - x[0] * data[i].alt - x[1]) * data[i].alt;
    g[1] -= 2 * (data[i].temp - x[0] * data[i].alt - x[1]);
  }
  printf("g[0] = %f, g[1]=%f\n", g[0], g[1]);
}