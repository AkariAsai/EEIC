#include <stdio.h>

#define NUMFRT 2
#define MAXCHAR 50

int main()
{
  char instrument[MAXCHAR] = "Pen";
  char fruit[NUMFRT][MAXCHAR] = {"Apple", "Pineapple"};
  int i;

  for (i = 0; i < NUMFRT; i++){
    printf("I have a %s.\n",instrument);
    printf("I have a %s.\n", fruit[i]);
    printf("...Uh, %s %s\n",fruit[i], instrument);
    printf("\n");
  }
  for (i = 0; i < NUMFRT; i++){
      printf("%s %s, ",fruit[i], instrument);
  }
  printf("\n");
  printf("...Uh, %s ", instrument);

  for (i = 0; i < NUMFRT; i++){
    printf("%s ", fruit[NUMFRT -i -1]);
  }

  printf("%s!\n", instrument );
  return 0;
}
