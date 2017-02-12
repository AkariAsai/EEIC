// This is combinatio of nearest neighbor and opt2.
/*
   n = 3 total distance = 89.790041
   n = 5 total distance =  110.417246
   n = 8 total distance =  138.864024
   n = 10 total distance =  148.256097
   n = 20 total distance =  194.415321
   n = 30 total distance =  250.706441
 */

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
double ct_distance[MAX_CITIES][MAX_CITIES] = {{0}};

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

  route[0] = 0; // Start from city[0]

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
int is_terminated(int num[], int N) {
  for (int i = 0; i < N; i++) {
    if (num[i] != 1)
      return 0;
  }
  return 1;
}

void calculate_city_distance(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (ct_distance[j][i] == 0) {
        ct_distance[i][j] = distance(i, j);
      } else {
        ct_distance[i][j] = ct_distance[j][i];
      }
    }
  }
}

int is_all_visited(int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    if (result[i] == 1)
      sum++;
  }
  return sum == n - 1;
}

void create_initial(int n) {
  calculate_city_distance(n);
  int idx = 0;
  int current = 0;
  result[current] = current;
  visited[current] = 1;
  int nearest = 0;
  while (idx < n - 1) {
    double min_dis = 4853729286096705926;
    for (int i = 0; i < n; i++) {
      if (i != current && visited[i] == 0 &&
          ct_distance[current][i] < min_dis) {
        min_dis = ct_distance[current][i];
        nearest = i;
      }
    }
    idx++;
    result[idx] = nearest;
    current = nearest;
    visited[current] = 1;
  }
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

void improve_route(int n) {
  srand((unsigned)time(NULL));
  int count = 0;
  int temp[MAX_CITIES];
  double distance1;
  double distance2;
  while (count < 60000) {
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
  improve_route(n);

  printf("total distance = %f\n", calculate_distance(result, n));
  plot_cities(fp, n, result);

  return 0;
}
