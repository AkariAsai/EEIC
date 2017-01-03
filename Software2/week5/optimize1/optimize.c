#include "optimize.h"
#include "func.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

House data[1000];

int exa = 0;

void open_data() {
  FILE *fp;
  fp = fopen("housing.csv", "r");
  int id;
  double rm;
  double price;
  while (fscanf(fp, "%d,%lf,%lf", &id, &rm, &price) != EOF) {
    data[id].id = id;
    data[id].rm = rm;
    data[id].price = price;
  }
  exa = id;
  fclose(fp);
}

double calc_norm(const int dim, double v[]) {
  double tmp = 0;
  int i = 0;
  for (i = 0; i < dim; i++) {
    tmp += v[i] * v[i];
  }
  tmp = sqrt(tmp);
  return tmp;
}

int optimize(const double alpha, const int dim, double x[],
             void (*calc_grad)(const double[], double[], House[1000]),
             double (*calc_value)(const double[], House[1000])) {
  int i;
  open_data();

  double *g = malloc(dim * sizeof(double));
  int iter = 0;
  while (++iter < 100000) {

    (*calc_grad)(x, g, data);
    const double norm = calc_norm(dim, g);

    if (norm < 0.01) {
      break;
    }

    for (i = 0; i < dim; i++) {
      x[i] -= alpha * g[i];
    }
  }
  for (i = 0; i < dim; i++) {
    printf("x[%d] = %7.4f ", i, x[i]);
  }
  putchar('\n');

  free(g);

  return iter;
}
