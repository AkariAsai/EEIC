#include <stdio.h>
#include <stdlib.h>

int comp_int(const void *x0, const void *x1) {
  const int *p0 = x0; // x0 is interpreted as a pointer to an integer
  const int y0 = *p0; // y0 is the int value that exists at p0
  //  const int y0 = *(int*)x0;  // The above can be written in one line.

  const int *p1 = x1;
  const int y1 = *p1;
  //  const int y1 = *(int*)x1;

  if (y0 < y1)
    return 1;
  if (y0 > y1)
    return -1;
  return 0;
}

int main() {
  int v[] = {13, 4, 9, 15, 7};
  const int n = sizeof(v) / sizeof(v[0]);

  qsort(v, n, sizeof(v[0]), comp_int);

  int i;
  for (i = 0; i < n; i++) {
    printf("v[%d] = %d\n", i, v[i]);
  }

  return 0;
}

/*
   分割コンパイルについてのメモ
   $ gcc –c main.c
   $ gcc –c solve.c
   $ gcc –c plot.c
   して
   gcc main.o solve.o plot.o
   するとそれら.oファイルを用いた実行ファイルが作成される。

   Makefile が存在するディレクトリで
   $ make
   とすると、main.o, solve.o, plot.o, a.out が順々に作成される
   a.out: main.o solve.o plot.o
   gcc main.o solve.o plot.o
   main.o: main.c
   gcc –c main.c
   solve.o: solve.c
   gcc –c solve.c
   plot.o: plot.c
   gcc –c plot.c
   ※ target を省略した場合、最初のターゲットが指定されたとみなされ

   結局同じ内容を
   CC = gcc
   OBJS = main.o solve.o plot.o
   a.out: $(OBJS)
   $(CC) $(OBJS)
   で記述できるよ！
 */
