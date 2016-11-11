#include <stdio.h>
#include<string.h>
int roman2num(char*);
int convertChar2int(char cha);
int main(){
  printf("XIV = %d\n", roman2num("XIV"));//14
  printf("CDXCV = %d\n", roman2num("CDXCV"));//495
  printf("MCMXLV = %d\n", roman2num("MCMXLV"));//1945
  printf("MMMCMXCIX = %d\n", roman2num("MMMCMXCIX"));//3999
  return 0;
}

int roman2num(char *s){
  int len = strlen(s);
  int total = 0;
  for (int i = 0;i < len; i++){
    if(*s == 'I' && i < len -1){
      total -= 2;
    }
    if 
    total += convertChar2int(*s);
    s++;
  }
  return total;
  
}

int adjust(char cha, int prefix){
  if (prefix)
  
}
int convertChar2int(char cha){
  int num = 0;
  switch(cha){
  case 'I':
    num = 1;
      break;
    case 'V':
      num = 5;
      break;
  case 'X':
    num  = 10;
    break;
  case 'L':
    num = 50;
    break;
  case 'C':
    num = 100;
    break;
  case 'D':
    num = 500;
    break;
  case 'M':
    num = 1000;
    break;
  default:
    break;
      
  }
  printf("num is  %d\n",num);
  return num;
  
}

