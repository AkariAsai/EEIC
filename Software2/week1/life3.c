#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 50
#define WIDTH 70

int cell[HEIGHT][WIDTH];

//@brief This is a method to save initial cells status. If cell[i][j] isn't
// nil(That means the cell should have a creature), it add '#' in the same
// position of file.Otherwise, it puts ' ' like the original.
void save_file() {
  FILE *fp;
  if ((fp = fopen("cells_2.txt", "w")) == NULL) {
    fprintf(stderr, "error: cannot open a file.\n");
    return;
  }

  int i, j;
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      fputc(cell[i][j] ? '#' : ' ', fp);
    }
    fputc('\n', fp);
  }
  fputc('\n', fp);
  fclose(fp);
}

//@brief This is a method to load the infomation of cell's initial position.
void init_cells_file() {
  int row = 0, col = 0;
  char c;
  FILE *fp1;
  fp1 = fopen("cells_2.txt", "r");

  while ((c = fgetc(fp1)) != EOF) {
    if (c == '\n') {
      cell[row][col] = (c == '#') ? 1 : 0;
      row++;
      col = 0;
    } else {
      cell[row][col] = (c == '#') ? 1 : 0;
      col++;
    }
  }
  save_file();
  fclose(fp1);
}

void print_cells(FILE *fp) {
  int i, j;

  fprintf(fp, "----------\n");

  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      const char c = (cell[i][j] == 1) ? '#' : ' ';
      fputc(c, fp);
    }
    fputc('\n', fp);
  }
  fflush(fp);

  sleep(1);
}

int count_adjacent_cells(int i, int j) {
  int n = 0;
  int k, l;
  for (k = i - 1; k <= i + 1; k++) {
    if (k < 0 || k >= HEIGHT)
      continue;
    for (l = j - 1; l <= j + 1; l++) {
      if (k == i && l == j)
        continue;
      if (l < 0 || l >= WIDTH)
        continue;
      n += cell[k][l];
    }
  }
  return n;
}

int isAlive(int sum, int current) {
  switch (sum) {
  case 2:
    return current ? 1 : 0;
  case 3:
    return 1;
  default:
    return 0;
  }
}

void update_cells() {
  int i, j;
  int cell_next[HEIGHT][WIDTH];

  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      cell_next[i][j] = 0;
      const int n = count_adjacent_cells(i, j);
      if (isAlive(n, cell[i][j])) {
        cell_next[i][j] = 1;
      }
    }
  }

  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      cell[i][j] = cell_next[i][j];
    }
  }
}

int count_alive_cells() {
  int i, j, sum = 0;
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      sum += cell[i][j];
    }
  }
  return sum;
}

int main() {
  int gen;
  FILE *fp;

  if ((fp = fopen("cells.txt", "a")) == NULL) {
    fprintf(stderr, "error: cannot open a file.\n");
    return 1;
  }
  init_cells_file();
  print_cells(fp);

  for (gen = 1;; gen++) {
    printf("generation = %d\n", gen);
    printf("%d cells are alives.\n", count_alive_cells());
    update_cells();
    print_cells(fp);
  }

  fclose(fp);

  return 0;
}

void save_cells_file() {
  int i, j;
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
    }
  }
}
