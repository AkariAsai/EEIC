#include <stdio.h>
#include<stdlib.h>
#include <math.h>

 void stats(int, double*,double*, double*);

int main(int argc, char** argv){
  double *data;
  double mean, variance;
  int i;
  data = (double*)malloc(sizeof(int) * argc);
  for (i = 0; i < argc - 1; i++){
    data[i] = atof(argv[i+1]);
  }
  
  stats(argc - 1, data, &mean, &variance);
  if (argc > 1){
    printf("mean = %f, variance = %f\n", mean, variance);
  }
  return 0;
}

void stats(int N, double *data, double *mean, double *variance){
  double m_sum = 0;
  double v_sum = 0;
  int i;
  for (i = 0; i < N; i++){
    m_sum += data[i];
  }
  *mean = m_sum/(double)N;
  for (i = 0; i < N; i++){
    v_sum += pow(*data - *mean, 2);
    data++;
  }
  *variance = v_sum/(double)N;
}

