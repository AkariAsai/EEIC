#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 30
#define HEIGHT 15

int main()
{
  char matrix[HEIGHT + 1][WIDTH + 1];
  int x, y;

  for (x = 0;x< HEIGHT;x++){
    for (y = 0;y < WIDTH;y ++){
     matrix[x][y] = '.';
    }
  }
  for (x = 0;x < HEIGHT;x++){
    for (y = 0;y < WIDTH; y++){
      if ((x - HEIGHT/2) * (x - HEIGHT/2) + (y - WIDTH/2) * (y- WIDTH/2)  < HEIGHT * HEIGHT /4) {
	       matrix[x][y] = '*';
      }
    }
  }

  for (x = 0;x < HEIGHT;x ++){
    for (y = 0;y< WIDTH;y++){
      putchar(matrix[x][y]);
      putchar(' ');
    }
    putchar('\n');
  }
  return 0;
}
