#include <stdio.h>

 int main(int argc, char** argv){
  char *fileName = argv[1];
  FILE *fp, *fp2;

  fp = fopen(fileName, "r");

  char prev = '.';
  char c;
  int row = 0,cul = 0;
  while((c=getc(fp)) != EOF){
    if (c == '\n'){
      row++;
    }
    if (c == ' '){
	    cul++;
    }
  }
  fseek(fp,  0L, SEEK_END);
  int i = 0, j = 0, k = 0;
  char temp[10];
  while((c=getc(fp)) != EOF){
    if (c == ' '){



        }
        else if (c == '\n'){
        }
        }
      }
    }

    }
  }





  return 1;
 }
