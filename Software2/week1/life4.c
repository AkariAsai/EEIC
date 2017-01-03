/*
   今回加えた特殊ルールは以下の通りです。
   #特徴追加の目的
   -通常のライフゲームとはやや趣旨を変え、生物の食物連鎖、主に捕食者、被食者の急増殖とその絶滅の観察をするために幾つかのルール追加を行った。
   -自然界には食物連鎖（生態系ピラミッド）が存在し、これを単純化してしまうと、植物（草食動物によって食われるもの）、草食動物、肉食動物（食物連鎖の頂点）と考えることができる。
   -一見、この構造は頂点に立つ肉食動物に有利なようだが、実際には下位層生物に何重にも依存している肉食動物は食物連鎖においてもっとも過繁殖、急激な下位生物の個体数の減少に影響を受けやすく、絶滅に陥りやすい。
   -今回の追加では、植物、捕食者、被食者の三つの生物種を加え、それぞれが相互に反応する中でどう動くのか、また自然災害や急激な個体数の増加はどうそれぞれの生物種に影響を与えるのかをシミュレーションした。

   ＃追加した特徴
     1.植物、捕食者、被食者
       本来のライフゲームのルールにおいては、周囲に3つの生物が存在する場合に誕生、周囲に2もしくは3の生物が存在するときに維持、とされていました。
       今回は植物(1)に加えて、被食者(2）&捕食者(3)システムを導入し、隣接するセルが自身と同じ種類であれば通常通りのルールを、仮に自身が2であった場合は隣接するセルのうち一つでも（3）であれば滅亡になります。
       また自身が(3)であれば、周辺の空いているセルの一部に生命（3）を誕生させることができます。
       また被食者は近くに(1)が存在していた場合、一定確率で空白セルに自身(2)を誕生させることができます。
       （周辺のセル全てに被食者、捕食者を新たに誕生させないのは、過繁殖は過密による絶滅をもたらすため）
       この場合日食される側はより容易に絶滅の危険性が生じてしまいますが、ここは二つ目のルールにより、一定確率で大量増殖が可能です。
     2.カンブリア爆発
       5%の確率で発生するイベント。これが発生する場合、すべてのセルのうち12.5%のセルで生命が発生し、うち70％が植物,
     20%は草食動物、10%が肉食動物になる。
     3.火山噴火
     　5%の確率で発生。画面上の中心エリアの生命すべてが死滅する。

   #観察した結論
   -最初のセルの発生を完全ランダム、全体の5パーセントのセルに発生にした場合、過密により開始後すぐに急激にその数が減少してしまう。
   -捕食者、被食者について観察をしてみると、やはり一匹でも被食者がいれば次ターンで少なくとも自身を除く1セル以上を発生させられる捕食者がある程度有利にはなっている。
   -一方で、捕食者は自身の急増殖により被食者を食べつくしてしまうだけでなく、過密により自身の絶滅も招いてしまう。
   -その結果、開始後10ターン目以降、またランダムに発生するカンブリア爆発イベント（急繁殖）のち一定ターンを超えると捕食者はほぼ絶滅し、被食者のみが残ることになる。
   -つまり下層生物の急繁殖は上層生物の一時的な増加と下層生物の減少、そして結果的に過密によって上層生物が減少することにより元のバランスに戻る。
   -直接食物連鎖で関わりのないどうし（肉食動物と植物）は何ターンでも共存が可能である。

   #反省
   -食物連鎖に関するおおよそのシミュレーションはできたものの、発生などを群れなどの可能性を考慮せず乱数生成で行っているため、シミューレショントしては現実の状況に適していない。
   -乱数を発生をrand()でほぼ行っているため精度にはやや難がある。
   -今回はベースのライフゲームと同様、植物の絶滅/誕生/意地を全て同時に確認している（cellとcell_nextによる管理）。
   しかし現実世界において、絶滅、維持などはある程度の時間さがあるはず。そのズレを追加すべきだった。
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 50
#define WIDTH 70

int cell[HEIGHT][WIDTH];

void init_cells_random() {
  int i, j, num;
  srand((unsigned)time(NULL));
  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      cell[i][j] = 0;
      num = rand() % 40;
      if (num == 1 || num == 2 || num == 3) {
        cell[i][j] = num;
      }
    }
  }
}

char creature(int i) {
  //@brief それぞれの生物を代表する一文字を返すための関数。
  switch (i) {
  case 1:
    return 'w';
  case 2:
    return '*';
  case 3:
    return '%';
  default:
    return ' ';
  }
}

void add_cell(int num, FILE *fp) {
  //@brief セルの色、代表する文字を変えるための関数。
  //@details 獲物→黄色(*)、捕食者→赤(%)、通常のセル→白(#)。
  const char c = creature(num);
  switch (num) {
  case 2:
    fputs("\x1b[37m", fp);
    fputc(c, fp);
    break;
  case 3:
    fputs("\x1b[31m", fp);
    fputc(c, fp);
    break;
  default:
    fputs("\x1b[32m", fp);
    fputc(c, fp);
    break;
  }
}

void print_cells(FILE *fp) {
  int i, j;

  fprintf(fp, "----------\n");

  for (i = 0; i < HEIGHT; i++) {
    for (j = 0; j < WIDTH; j++) {
      add_cell(cell[i][j], fp);
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

//@brief　捕食者の周辺に被食者がいる場合、1を返す関数。つまり肉食動物のそばに草食動物がいる場合ないし草食動物のそばに植物がある場合、この関数で1が返される時、後述のbreed_hunter関数が呼ばれる。
int isBreed(int i, int j) {
  int isHerbivore = (cell[i][j] == 2);
  int k, l;
  for (k = i - 1; k <= i + 1; k++) {
    if (k < 0 || k >= HEIGHT)
      continue;
    for (l = j - 1; l <= j + 1; l++) {
      if (k == i && l == j)
        continue;
      if (l < 0 || l >= WIDTH)
        continue;
      //@dertails
      if ((cell[k][l] == 1 && isHerbivore) ||
          (cell[k][l] == 2 && !isHerbivore)) {
        return 1;
      }
    }
  }
  return 0;
}

//@brief　isBreed()が1の時呼ばれ、捕食者を繁殖させる。
void breed_hunter(int i, int j, int cell_next[HEIGHT][WIDTH]) {
  int k, l;
  int isHerbivore = (cell[i][j] == 2);
  for (k = i - 1; k <= i + 1; k++) {
    if (k < 0 || k >= HEIGHT)
      continue;
    for (l = j - 1; l <= j + 1; l++) {
      if (k == i && l == j)
        continue;
      if (l < 0 || l >= WIDTH)
        continue;
      if (cell[k][l] == 0 || l % 4 == 0) {
        cell_next[k][l] = (isHerbivore) ? 2 : 3;
      }
    }
  }
}

//@brief
//被食者の周辺に捕食者がいないか確認する関数。捕食者が周辺のセルに一つてもいれば1を返し、被食者は死亡する。
int isKilled(int i, int j) {
  int k, l;
  int isHerbivore = (cell[i][j] == 2);
  for (k = i - 1; k <= i + 1; k++) {
    if (k < 0 || k >= HEIGHT)
      continue;
    for (l = j - 1; l <= j + 1; l++) {
      if (k == i && l == j)
        continue;
      if (l < 0 || l >= WIDTH)
        continue;
      if ((cell[k][l] == 2 && !isHerbivore) ||
          (cell[k][l] == 3 && !isHerbivore)) {
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
        //セルが被食者の場合、周辺に捕食者がいないかを確認し、仮に本来のライフゲームの生存ルールを満たしていても、一つでも捕食者が周辺位いれば死亡。
        if ((cell[i][j] == 2 || cell[i][j] == 1) && isKilled(i, j)) {
          cell_next[i][j] = 0;
        } else {
          cell_next[i][j] = cell[i][j];
          //セルが捕食者の場合、周辺にいる被食者を殺し食べることができれば、一定確率で空白のセルに新たな生命を生み出すことができる。
          if ((cell[i][j] == 3 && isBreed(i, j)) ||
              (cell[i][j] == 2 && isBreed(i, j))) {
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
      //セルが1,2,3のいずれかであれ、0以外であれば生きているセルにとみなし1を加算する。
      if (cell[i][j]) {
        sum++;
      }
    }
  }
  return sum;
}

//@brief追加した特徴の2,3に当たる部分。
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
      num = rand() % 10;
      if (num == 0) {
        num = rand() % 10;
        if (num % 7 == 0)
          cell[i][j] = 3;
        else if (num % 3 == 0)
          cell[i][j] = 2;
        else
          cell[i][j] = 1;
      }
    }
  }
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
    //@brief
    // erはランダムな数を格納する。この乱数を元に5％の確率で急激な繁殖もしくは自然災害による全滅が発生する。
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
