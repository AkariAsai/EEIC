#include <stdio.h>
#include<stdlib.h>
#include <math.h>

#define N 3

void inverse(double**);
void init_inverse(char**);

int main(int argc, char** argv){
  double **matrix;
  matrix = (double**)malloc(sizeof(int*)*N);
  matrix[0] = (double *)malloc(sizeof(int)*N);
  matrix[1] = (double *)malloc(sizeof(int)*N);
  int i, j;
  int r,c;

  matrix[0][0] = atof(argv[1]);
  matrix[0][1] = atof(argv[2]);
  matrix[1][0] = atof(argv[3]);
  matrix[1][1] = atof(argv[4]);
  
  inverse(matrix);
 
  if (argc > 1){
    printf("The inverse of matrix : \n");
    for (i = 0; i <2; i++){
      printf("%f", matrix[0][i]);
      printf(" ");
    }
    printf("\n");
    for (i = 0; i <2; i++){
      printf("%f", matrix[1][i]);
      printf(" ");
    }
    printf("\n");
  }

  return 0;
}

void inverse(double **matrix){
  double numer, odd_denom, even_denom;
  odd_denom = matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
  even_denom =  matrix[1][0]*matrix[1][0] - matrix[0][0]*matrix[1][1];
  
  matrix[0][0] = matrix[1][1]/odd_denom;
  matrix[0][1] = matrix[0][1]/even_denom;
  matrix[1][0] = matrix[1][0]/odd_denom;
  matrix[1][1] = matrix[0][0]/odd_denom;
 
}

void init_inverse(char** argv){
}



