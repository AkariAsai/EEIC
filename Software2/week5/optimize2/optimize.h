#ifndef OPTIMIZE_OPTIMIZE_H
#define OPTIMIZE_OPTIMIZE_H

typedef struct {
  int id;       // id
  double lstat; // number of rooms
  double price; // house price
} House;

int optimize(const double alpha, const int dim, double x[],
             void (*calc_grad)(const double[], double[], House[1000]),
             double (*calc_value)(const double[], House[1000]));

#endif
