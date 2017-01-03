#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 70
#define HEIGHT 40
#define MAX_CITIES 1000

typedef struct {
  int x;
  int y;
} City;

City city[MAX_CITIES];
int visited[MAX_CITIES] = {0};
char map[WIDTH][HEIGHT];
int result[MAX_CITIES];
int temp[MAX_CITIES];
double prev;

int max(const int a, const int b) { return (a > b) ? a : b; }

void swap(int *x, int *y) {
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

unsigned int xorshift() {
  static unsigned int x = 1;
  static unsigned int y = 2;
  static unsigned int z = 3;
  static unsigned int w = 4;
  unsigned int t;

  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

int random_integer(int m) { return xorshift() % m; }

void shuffle(int ary[], int size) {
  srand(clock());
  for (int i = 0; i < size; i++) {
    int j = rand() % size;
    int t = ary[i];
    ary[i] = ary[j];
    ary[j] = t;
  }
}

void draw_line(const int x0, const int y0, const int x1, const int y1) {
  int i;
  const int n = max(abs(x1 - x0), abs(y1 - y0)) + 1;
  for (i = 0; i <= n; i++) {
    const int x = x0 + i * (x1 - x0) / n;
    const int y = y0 + i * (y1 - y0) / n;
    if (map[x][y] == ' ')
      map[x][y] = '*';
  }
}

void draw_route(const int n, const int *route) {
  if (route == NULL)
    return;

  int i;
  for (i = 0; i < n; i++) {
    const int c0 = route[i];
    const int c1 = (i < n - 1) ? route[i + 1] : route[0];
    draw_line(city[c0].x, city[c0].y, city[c1].x, city[c1].y);
  }
}

void plot_cities(FILE *fp, const int n, const int *route) {
  int i, j, x, y;

  fprintf(fp, "----------\n");

  memset(map, ' ', sizeof(map));

  for (i = 0; i < n; i++) {
    char buf[100];
    sprintf(buf, "C_%d", i);
    for (j = 0; j < strlen(buf); j++) {
      const int x = city[i].x + j;
      const int y = city[i].y;
      map[x][y] = buf[j];
    }
  }

  draw_route(n, route);

  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
      const char c = map[x][y];
      fputc(c, fp);
    }
    fputc('\n', fp);
  }

  fflush(fp);
}

double distance(const int i, const int j) {
  const double dx = city[i].x - city[j].x;
  const double dy = city[i].y - city[j].y;
  return sqrt(dx * dx + dy * dy);
}

double solve(const int n, int route[]) {
  int i;

  route[0] = 0;
  for (i = 1; i < n; i++) {
    route[i] = i;
  }
  double sum_d = 0;
  for (i = 0; i < n; i++) {
    const int c0 = route[i];
    const int c1 = (i < n - 1) ? route[i + 1] : route[0];
    sum_d += distance(c0, c1);
  }

  return sum_d;
}

// Make an initial random route usinf suffle function which is defined above.
void create_initial(int n) {
  for (int i = 0; i < n; i++) {
    result[i] = i;
  }
  shuffle(result, n);
}

double calculate_distance(int route[], int n) {
  double sum = 0;
  for (int i = 0; i < n; i++) {
    if (i != n - 1)
      sum += distance(route[i], route[i + 1]);
    else
      sum += distance(route[i], route[0]);
  }
  return sum;
}

//@brief Thie is the first version of Clibming method.
/*Checking all of the possible combincation of i, j,
   and if the distance becomes shorter after swaping two cities, it increment
   the
   counter by 1.
   If the counter is still 0 after the end of the double for loop, it means
   there
   are no spaces to improve,
   so it terminate the while roop.
   It works but the distance becomes a bit longer than the second ver, swapping
   randomly and keep doing for 60k times.
 */

void improve_route_ver1(int n) {
  double distance1;
  double distance2;
  while (1) {
    int count = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i != j) {
          distance1 = calculate_distance(result, n);
          swap(&result[i], &result[j]);
          distance2 = calculate_distance(result, n);
          if (distance2 > distance1) {
            swap(&result[i], &result[j]);
          } else {
            count++;
          }
        }
      }
    }
    if (!count)
      break;
  }
}

//@brief This is the second method of Clibming.
/*In the first version which i wrote above can return reasonable distance, but I
   found I could improve more from the picture,
   so here I just generate randome numbers and swapping if the distance can be
   improved.
   Generally, it reterns shorter distance and can return 180~190 if the initial
   route is a good one.
 */
void improve_route_ver2(int n) {
  srand((unsigned)time(NULL));
  int count = 0;
  int temp[MAX_CITIES];
  double distance1;
  double distance2;
  while (count < 50000) {
    int c0 = random_integer(n);
    int c1 = random_integer(n);
    if (c0 != c1) {
      distance1 = calculate_distance(result, n);
      swap(&result[c0], &result[c1]);
      distance2 = calculate_distance(result, n);
      if (distance2 > distance1) {
        swap(&result[c0], &result[c1]);
      }
      count++;
    }
  }
}

int main(const int argc, const char **argv) {
  FILE *fp;
  const char *map_file = "map.txt";
  if ((fp = fopen(map_file, "a")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", map_file);
    return 1;
  }

  if (argc != 2) {
    fprintf(stderr, "error: please specify the number of cities.\n");
    exit(1);
  }

  const int n = atoi(argv[1]);
  assert(n > 1 && n <= MAX_CITIES);

  int i;
  for (i = 0; i < n; i++) {
    city[i].x = rand() % (WIDTH - 5);
    city[i].y = rand() % HEIGHT;
  }
  int route[MAX_CITIES];
  create_initial(n);
  plot_cities(fp, n, NULL);
  sleep(1);

  const double d = solve(n, route);
  printf("The initial route distance = %f\n", d);
  improve_route_ver2(n);
  printf("total distance = %f\n", calculate_distance(result, n));
  plot_cities(fp, n, result);

  return 0;
}
