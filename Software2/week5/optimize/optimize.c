#include "optimize.h"
#include "func.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
             void (*calc_grad)(const double[], double[]),
             double (*calc_value)(const double[])) {
  int i;

  double *g = malloc(dim * sizeof(double));
  int iter = 0;
  while (++iter < 10) {

    (*calc_grad)(x, g);
    printf("f_value = %f\n", calc_value(x));
    const double norm = calc_norm(dim, g);
    printf("%3d norm = %7.4f", iter, norm);

    for (i = 0; i < dim; i++) {
      printf(", x[%d] = %7.4f", i, x[i]);
    }
    putchar('\n');

    if (norm < 0.001)
      break;

    for (i = 0; i < dim; i++) {
      x[i] -= alpha * g[i];
    }
  }
  free(g);

  return iter;
}
