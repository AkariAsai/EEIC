#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 75
#define HEIGHT 40

const double G = 1.0; // gravity constant

struct star {
  double m;
  double x;  // position_x
  double y;  // position_y
  double vx; // velocity_x
  double vy; // velocity_y
};

struct star stars[] = {{1.0, -10.0, -10.0, 0.0, 0.0},
                       {0.5, 10.0, 10.0, 0.2, 0.3},
                       {0.3, -9.0, -9.0, -0.1, -0.1}};

const int nstars = sizeof(stars) / sizeof(struct star);

void plot_stars(FILE *fp, const double t) {
  int i;
  char space[WIDTH][HEIGHT];

  memset(space, ' ', sizeof(space));
  for (i = 0; i < nstars; i++) {
    const int x = WIDTH / 2 + stars[i].x;
    const int y = HEIGHT / 2 + stars[i].y;
    if (x < 0 || x >= WIDTH)
      continue;
    if (y < 0 || y >= HEIGHT)
      continue;
    char c = 'o';
    if (stars[i].m >= 1.0) {
      c = 'O';
    } else if (stars[i].m < 0.5) {
      c = '*';
    }
    space[x][y] = c;
  }

  int x, y;
  fprintf(fp, "----------\n");
  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++)
      fputc(space[x][y], fp);
    fputc('\n', fp);
  }
  fflush(fp);

  printf("t = %5.1f", t);
  for (i = 0; i < nstars; i++)
    printf(", stars[%d].x = %7.2f,  stars[%d].y = %7.2f\n vx  = %f  vy  = %f\n",
           i, stars[i].x, i, stars[i].y, stars[i].vx, stars[i].vy);
  printf("\n");
}

void update_velocities(const double dt) {
  int i, j;
  for (i = 0; i < nstars; i++) {
    double ax = 0;
    double ay = 0;
    for (j = 0; j < nstars; j++) {
      if (j != i) {
        double dis = sqrt(pow(stars[i].x - stars[j].x, 2) +
                          pow(stars[i].y - stars[j].y, 2));
        ax += (G * stars[j].m / pow(dis, 3)) * (stars[j].x - stars[i].x);
        ay += (G * stars[j].m / pow(dis, 3)) * (stars[j].y - stars[i].y);
      }
    }
    stars[i].vx += ax * dt;
    stars[i].vy += ay * dt;
  }
}

void update_positions(const double dt) {
  int i;
  for (i = 0; i < nstars; i++) {
    stars[i].x += stars[i].vx * dt;
    stars[i].y += stars[i].vy * dt;
  }
}

int main(int argc, char **argv) {
  const char *filename = "space.txt";
  const double dt = atof(argv[1]);

  FILE *fp;
  if ((fp = fopen(filename, "a")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", filename);
    return 1;
  }
  const double stop_time = 400;
  int i;
  double t = 0;
  printf("num  of stars is %d\n", nstars);
  for (i = 0, t = 0; t <= stop_time; i++, t += dt) {
    update_velocities(dt);
    update_positions(dt);
    if (i % 10 == 0) {
      plot_stars(fp, t);
      usleep(200 * 1000);
    }
  }
  fclose(fp);

  return 0;
}
