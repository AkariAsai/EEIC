#include "func_ransac.h"
#include "optimize.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

House data[1000];

double good_model[150][2]; // This is an array to keep good momdels where the
int model_count = 0;       // number of errors less than 10.

void sample_optimize(const double alpha, const int dim, double x[],
                     void (*calc_grad)(const double[], double[], House[1000]),
                     double (*calc_value)(const double[], House[1000]));

double calculate_distance(double y, double y_predict);
double predict(double rm, double x[]);
double calculate_cost(double x[]);

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

int optimize_ransac(const double alpha, const int dim, double x[],
                    void (*calc_grad)(const double[], double[], House[1000]),
                    double (*calc_value)(const double[], House[1000])) {
  // int i;
  int i, iter = 0;
  printf("hello");
  open_data();

  for (i = 0; i < 150; i++) {
    sample_optimize(alpha, dim, x, calc_grad, calc_value);
  }
  double min_cost = 7892367850236728;
  double best_model[2] = {0};
  for (i = 0; i < model_count; i++) {
    printf("model[%d][0]: %f model[%d][1]:%f , cost : %f\n", i,
           good_model[i][0], i, good_model[i][1],
           calculate_cost(good_model[i]));
    if (min_cost > calculate_cost(good_model[i])) {
      min_cost = calculate_cost(good_model[i]);
      best_model[0] = good_model[i][0];
      best_model[1] = good_model[i][1];
    }
  }
  printf("x[0]: %f, x[1]: %f\n", best_model[0], best_model[1]);

  return iter;
}

void sample_optimize(const double alpha, const int dim, double x[],
                     void (*calc_grad)(const double[], double[], House[1000]),
                     double (*calc_value)(const double[], House[1000])) {
  int i;
  x[0] = 0;
  x[1] = 0;
  double *g = malloc(dim * sizeof(double));
  int iter = 0;
  while (++iter < 10000) {

    (*calc_grad)(x, g, data);
    const double norm = calc_norm(dim, g);

    if (norm < 0.01) {
      break;
    }

    for (i = 0; i < dim; i++) {
      x[i] -= alpha * g[i];
    }
  }
  int errors = 0;
  for (i = 0; i < 505; i++) {
    if (calculate_distance(data[i].price, predict(data[i].rm, x)) > 5)
      errors++;
  }
  printf("x[0]:%f x[1]:%f\n", x[0], x[1]);
  if (errors < 150) {
    for (i = 0; i < dim; i++) {
      good_model[model_count][i] = x[i];
    }
    model_count++;
  }
  free(g);
}

double calculate_distance(double y, double y_predict) {
  return fabs(y - y_predict);
}

double predict(double rm, double x[]) { return rm * x[0] + x[1]; }

double calculate_cost(double x[]) {
  double total_cost = 0;
  for (int i = 0; i < 505; i++) {
    total_cost += calculate_distance(data[i].price, predict(data[i].rm, x));
  }
  return total_cost;
}
