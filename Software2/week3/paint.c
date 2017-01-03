#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 70
#define HEIGHT 40

#define MAX_HISTORY 100
#define BUFSIZE 1000

struct history {
  char *str;
  struct history *next;
};

typedef struct history History;

char canvas[WIDTH][HEIGHT];
char history[MAX_HISTORY][BUFSIZE];

const char *default_history_file = "history.txt";

void print_canvas(FILE *fp) {
  int x, y;

  fprintf(fp, "----------\n");

  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
      const char c = canvas[x][y];
      fputc(c, fp);
    }
    fputc('\n', fp);
  }
  fflush(fp);
}

void init_canvas() { memset(canvas, ' ', sizeof(canvas)); }

int max(const int a, const int b) { return (a > b) ? a : b; }

void draw_line(const int x0, const int y0, const int x1, const int y1) {
  int i;
  const int n = max(abs(x1 - x0), abs(y1 - y0));
  for (i = 0; i <= n; i++) {
    const int x = x0 + i * (x1 - x0) / n;
    const int y = y0 + i * (y1 - y0) / n;
    canvas[x][y] = '#';
  }
}

void draw_rect(const int x0, const int y0, const int width, const int height) {
  draw_line(x0, y0, x0 + width, y0);
  draw_line(x0 + width, y0, x0 + width, y0 + height);
  draw_line(x0, y0, x0, y0 + height);
  draw_line(x0, y0 + height, x0 + width, y0 + height);
};

void draw_circle(const int x0, const int y0, const int r) {
  for (int x = 0; x < HEIGHT; x++) {
    for (int y = 0; y < WIDTH; y++) {
      if (pow((x - x0 / 2), 2) + pow((y - y0 / 2), 2) < r * r / 4) {
        canvas[x][y] = '#';
      }
    }
  }
}

History *construct_history(char *str) {
  History *p = malloc(sizeof(History));
  char *s = malloc(strlen(str) + 1);
  strcpy(s, str);
  p->str = s;
  p->next = NULL;
  return p;
}

History *pop_front(History *begin) {
  assert(begin != NULL); // Don't call pop_front() when the list is empty
  History *p = begin->next;
  free(begin->str);
  free(begin);

  return p;
}

History *pop_back(History *begin) {
  assert(begin != NULL);

  while (begin->next) {
    if (!begin->next->next)
      begin->next = NULL;
  }
  return begin;
}

void save_history(const char *filename, const int history_size,
                  History *history) {
  if (filename == NULL)
    filename = default_history_file;

  FILE *fp;
  if ((fp = fopen(filename, "w")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", filename);
    return;
  }

  History *p = history;
  while (p) {
    fprintf(fp, "%s", p->str);
    p = p->next;
  }
  printf("saved as \"%s\"\n", filename);

  fclose(fp);
}

// Interpret and execute a command
//   return value:
//     0, normal commands such as "line"
//     1, unknown or special commands (not recorded in history[])
//     2, quit
int interpret_command(const char *command, int *hsize, History *history) {
  int i;
  char buf[BUFSIZE];
  strcpy(buf, command);

  buf[strlen(buf) - 1] = 0;

  const char *s = strtok(buf, " ");

  if (strcmp(s, "line") == 0) {
    int x0, y0, x1, y1;
    x0 = atoi(strtok(NULL, " "));
    y0 = atoi(strtok(NULL, " "));
    x1 = atoi(strtok(NULL, " "));
    y1 = atoi(strtok(NULL, " "));
    draw_line(x0, y0, x1, y1);
    return 0;
  }

  if (strcmp(s, "rect") == 0) {
    int x0, y0, width, height;
    x0 = atoi(strtok(NULL, " "));
    y0 = atoi(strtok(NULL, " "));
    width = atoi(strtok(NULL, " "));
    height = atoi(strtok(NULL, " "));
    draw_rect(x0, y0, width, height);
    return 0;
  }

  if (strcmp(s, "circle") == 0) {
    int x0, y0, r;
    x0 = atoi(strtok(NULL, " "));
    y0 = atoi(strtok(NULL, " "));
    r = atoi(strtok(NULL, " "));
    draw_circle(x0, y0, r);
    return 0;
  }

  if (strcmp(s, "save") == 0) {
    s = strtok(NULL, " ");
    save_history(s, *hsize, history);
    return 1;
  }

  if (strcmp(s, "undo") == 0) {
    init_canvas();
    if (history) {
      History *p = history;
      while (p->next) {
        interpret_command(history->str, NULL, history);
        p = p->next;
      }
      history = pop_back(history);
      hsize--;
    } else {
      printf("Are you serious?");
      hsize--;
    }
    return 1;
  }

  if (strcmp(s, "quit") == 0) {
    return 2;
  }

  printf("error: unknown command.\n");

  return 1;
}

int main() {
  const char *filename = "canvas.txt";
  FILE *fp;
  char buf[BUFSIZE];
  char *p_buf;
  History *history;

  if ((fp = fopen(filename, "a")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", filename);
    return 1;
  }

  init_canvas();
  print_canvas(fp);

  int hsize = 0; // history size
  while (1) {    //後で消す

    printf("%d > ", hsize);
    fgets(buf, BUFSIZE, stdin);
    p_buf = buf;

    const int r = interpret_command(buf, &hsize, history);
    if (r == 2)
      break;
    if (r == 0) {
      if (!history) {
        history = construct_history(p_buf);
      } else {
        history->next = construct_history(p_buf);
      }
      hsize++;
    }

    print_canvas(fp);
  }

  fclose(fp);

  return 0;
}
