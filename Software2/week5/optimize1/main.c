#include "func.h"
#include "optimize_ransac.h"
#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char **argv) {
  const double alpha = (argc == 2) ? atof(argv[1]) : 0.0023;

  int i;
  const int dim = f_dimension();

  double *x = malloc(dim * sizeof(double));
  for (i = 0; i < dim; i++) {
    x[i] = 0;
  }

  printf("alpha = %f\n", alpha);

  const int iter = optimize_ransac(alpha, dim, x, f_gradient, f_value);

  printf("number of iterations = %d\n", iter);

  free(x);

  return 0;
}
