#ifndef OPTIMIZE_RANSAC_H
#define OPTIMIZE_RANSAC_H

typedef struct {
  int id;       // id
  double rm;    // number of rooms
  double price; // house price
} House;

int optimize_ransac(const double alpha, const int dim, double x[],
                    void (*calc_grad)(const double[], double[], House[1000]),
                    double (*calc_value)(const double[], House[1000]));

#endif
