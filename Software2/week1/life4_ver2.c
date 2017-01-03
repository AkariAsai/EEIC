/*
   もともと課題4については一つのファイルで作成をしていたのですが、最初に実装した方（食物連鎖、ランダムな生物の発生、自然現象）と
   趣旨が大きく異なっていたため、二つのファイルに分けて作成しました。
   4.様々な形態の生命
    先立っての質問の答えを作成し、結果を観察するうちに、幾つかの特徴的な動きをするセルの集合体が存在することに気がついた（常に形が変動しないもの、開店しているもの）
    ここでは幾つか観察された特殊な生命体をあえて最初に追加し、それらがどのくらい長く存在しうるかを確認している。
    幾つかの生物種を作成し、それらがどれくらい生き残るかを確認した。
    参考：http://www.ochearno.net/entry/interesting_world_of_life_game
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 50
#define WIDTH 70

int cell[HEIGHT][WIDTH];

void add_creatures();
void eruption();
void cambrian_explosion();

void init_cells_random() {
  int i, j, num;
  srand((unsigned)time(NULL));
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      cell[i][j] = 0;
      num = rand() % 20;
      if (num == 1 || num == 2 || num == 3) {
        cell[i][j] = num;
      }
    }
  }
  for (i = 0; i < 5; i++) {
    add_creatures();
  }
}

void add_block(int i, int j) {
  cell[i][j] = 1;
  cell[i + 1][j] = 1;
  cell[i][j + 1] = 1;
  cell[i + 1][j + 1] = 1;
}

void add_beehive(int i, int j) {
  cell[i][j] = 1;
  cell[i][j + 1] = 1;
  cell[i + 1][j - 1] = 1;
  cell[i + 1][j + 2] = 1;
  cell[i + 2][j] = 1;
  cell[i + 2][j + 1] = 1;
}

void add_blinker(int i, int j) {
  int k;
  for (k = 0; k < 3; k++) {
    cell[i][j + k] = 1;
  }
}

//@brief This is a eruption method I mentioned as the third additional
// feature.
void eruption() {
  int x = WIDTH / 2 - 10;
  int y = HEIGHT / 2 - 10;

  int i, j;
  for (i = 0; i < 20; i++) {
    for (j = 0; j < 20; j++) {
      cell[x + i][y + j] = 0;
    }
  }
}

void cambrian_explosion() {
  int i, j, num;
  srand((unsigned)time(NULL));
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      num = rand() % 5;
      if (num == 0) {
        num = rand() % 4;
        cell[i][j] = (num % 4 == 0) ? 3 : 2;
      }
    }
  }
}

void add_creatures() {
  srand((unsigned)time(NULL));
  int i, j;
  i = rand() % (HEIGHT - 5);
  j = rand() % (WIDTH - 5);

  int kind = rand() % 3;
  switch (kind) {
  case 0:
    add_beehive(i, j);
    break;
  case 1:
    add_blinker(i, j);
  default:
    add_block(i, j);
  }
}

char creature(int i) {
  switch (i) {
  case 1:
    return '#';
  case 2:
    return '*';
  case 3:
    return '%';
  default:
    return ' ';
  }
}
void print_cells(FILE *fp) {
  int i, j;

  fprintf(fp, "----------\n");

  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      const char c = creature(cell[i][j]);
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

void breed_hunter(int i, int j, int cell_next[HEIGHT][WIDTH]) {
  int k, l;
  for (k = i - 1; k <= i + 1; k++) {
    if (k < 0 || k >= HEIGHT)
      continue;
    for (l = j - 1; l <= j + 1; l++) {
      if (k == i && l == j)
        continue;
      if (l < 0 || l >= WIDTH)
        continue;
      if (cell[k][l] == 0) {
        cell_next[k][l] = 3;
      }
    }
  }
}

int isKilled(int i, int j) {
  int k, l;
  for (k = i - 1; k <= i + 1; k++) {
    if (k < 0 || k >= HEIGHT)
      continue;
    for (l = j - 1; l <= j + 1; l++) {
      if (k == i && l == j)
        continue;
      if (l < 0 || l >= WIDTH)
        continue;
      if (cell[k][l] == 3) {
        return 1;
      }
    }
  }
  return 0;
}

int breed(int i, int j) {
  int k, l;
  for (k = i - 1; k <= i + 1; k++) {
    if (k < 0 || k >= HEIGHT)
      continue;
    for (l = j - 1; l <= j + 1; l++) {
      if (k == i && l == j)
        continue;
      if (l < 0 || l >= WIDTH)
        continue;
      if (cell[k][l] == 2) {
        return 1;
      }
    }
  }
  return 0;
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
        if (cell[i][j] == 2 && isKilled(i, j)) {
          cell_next[i][j] = 0;
        } else {
          cell_next[i][j] = cell[i][j];
          if (cell[i][j] == 3 && breed(i, j)) {
            breed_hunter(i, j, cell_next);
          }
        }
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
      if (cell[i][j]) {
        sum++;
      }
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

  init_cells_random();
  print_cells(fp);

  srand((unsigned)time(NULL));
  for (gen = 1;; gen++) {
    int erp = rand() % 20;
    printf("generation = %d\n", gen);
    printf("%d cells are alives.\n", count_alive_cells());
    if (erp == 0) {
      eruption();
    } else if (erp == 1) {
      cambrian_explosion();
    } else {
      update_cells();
    }
    print_cells(fp);
  }
  fclose(fp);

  return 0;
}
