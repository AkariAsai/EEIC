#include  <stdio.h>
#include <math.h>
  
int main(int argc, char** argv){
  char *fileName = argv[1];
  FILE *fp;()
  fp = fopen(fileName, "r");
  if (fp == NULL){
    printf("Failed to open the file\n");
    return 1;
  }
  int age = 0;
  double weight = 0;
  double hight = 0;
  double ageMax = 0, ageMin = 200, hightMax = 0, hightMin = 200, weightMax = 0, weightMin = 200;
  double ageSum = 0, weightSum = 0, hightSum = 0;
  double ageMean = 0, hightMean = 0, weightMean = 0;
  double ageSTDV = 0, hightSTDV = 0, weightSTDV = 0;
  int i;
  while ((fscanf(fp,"%*[^,],%d,%lf,%lf\n",&age, &weight, &hight)) != EOF){
	ageSum += age;
	weightSum += weight;
	hightSum += hight;
	ageMax = (age > ageMax)? age: ageMax;
	ageMin = (age < ageMin)? age: ageMin;
	hightMax =  (hight > hightMax)? hight:hightMax;
	hightMin = (hight < hightMin)? hight:hightMin;
	weightMax = (weight > weightMax)? weight: weightMax;
	weightMin = (weight < weightMin)? weight:weightMin;
	i++;
      }
      ageMean = ageSum/i;
      hightMean = hightSum/(double)i;
      weightMean = weightSum/(double)i;

      fclose(fp);
      fseek(fp, 0L, SEEK_SET);

    while ((fscanf(fp,"%*[^,],%d,%lf,%lf\n",&age, &weight, &hight)) != EOF){
	    ageSTDV = pow((age - ageMean), 2);
	    hightSTDV = pow((hight - hightMean), 2);
	    weightSTDV = pow((weight - weightMean), 2);	    
	  }
    ageSTDV = ageSTDV/(double)i;
    hightSTDV =  hightSTDV/(double)i;
    weightSTDV = weightSTDV/(double)i;
	  printf("Age mean: %f max: %f min:%f stdv %f\n", ageMean, ageMax, ageMin, ageSTDV);
	  
	  
	  }
       
