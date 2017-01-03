#include "optimize.h"
#include "func.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

House data[1000];

void open_data() {
  FILE *fp;
  fp = fopen("housing2.csv", "r");
  int id;
  double lstat;
  double price;
  while (fscanf(fp, "%d,%lf,%lf", &id, &lstat, &price) != EOF) {
    data[id].id = id;
    data[id].lstat = lstat;
    data[id].price = price;
    printf("id:%d lstat:%f price:%f\n", data[id].id, data[id].lstat,
           data[id].price);
  }
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
    // printf("f_value = %f\n", calc_value(x, data));
    const double norm = calc_norm(dim, g);
    // printf("%3d norm = %7.4f", iter, norm);

    if (norm < 0.001)
      break;

    for (i = 0; i < dim; i++) {
      x[i] -= alpha * g[i];
    }
  }

  for (i = 0; i < dim; i++) {
    printf(", x[%d] = %7.4f", i, x[i]);
  }
  putchar('\n');
  free(g);

  return iter;
}
