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

struct node {
  char *str;
  struct node *next;
};

typedef struct node Node;

char canvas[WIDTH][HEIGHT];

// Methods for constructing/manipulating Node.
Node *construct_node(char *str) {
  Node *p = malloc(sizeof(Node));
  char *s = malloc(strlen(str) + 1);
  strcpy(s, str);
  p->str = s;
  p->next = NULL;
  return p;
}

Node *push_front(Node *begin, const char *str) {
  // Create a new element
  Node *p = malloc(sizeof(Node));
  char *s = malloc(strlen(str) + 1);
  strcpy(s, str);
  p->str = s;
  p->next = begin;

  return p;
}

Node *pop_front(Node *begin) {
  assert(begin != NULL);
  Node *p = begin->next;
  free(begin->str);
  free(begin);

  return p;
}

Node *push_back(Node *begin, char *str) {
  if (begin == NULL) { // If the list is empty
    return construct_node(str);
  }

  Node *p = begin;
  while (p->next != NULL) {
    p = p->next;
  }
  // Create a new element
  Node *q = malloc(sizeof(Node));
  char *s = malloc(strlen(str) + 1);
  strcpy(s, str);
  q->str = s;
  q->next = NULL;

  p->next = q;

  return begin;
}

Node *pop_back(Node *begin) {
  assert(begin != NULL);

  Node *p = begin;
  while (begin->next) {
    if (!begin->next->next) {
      begin->next = NULL;
    } else {
      begin = begin->next;
    }
  }
  return p;
}

const char *default_history_file = "history.txt";
int interpret_command(const char *command, int *hsize, Node *node);
Node *construct_node(char *str);

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

// draw command
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

Node *load_file(int hsize, Node *node) {
  const char *filename = "history.txt";
  char command[100]; // need to be fized
  FILE *fp;

  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", filename);
    return 0;
  }

  while (fgets(command, sizeof(command), fp) != NULL) {
    const int r = interpret_command(command, &hsize, node);
    if (r == 2)
      break;
    if (r == 0) {
      node = push_back(node, command);
      hsize++;
    }
    print_canvas(fp);
  }
  fclose(fp);
  return node;
}

void save_history(const char *filename, const int history_size, Node *node) {
  if (filename == NULL)
    filename = default_history_file;

  FILE *fp;
  if ((fp = fopen(filename, "w")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", filename);
    return;
  }

  Node *p = node;
  while (p) {
    fprintf(fp, "%s", p->str);
    p = p->next;
  }
  printf("saved as \"%s\"\n", filename);
  fclose(fp);
}

int interpret_command(const char *command, int *hsize, Node *node) {
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
    save_history(s, *hsize, node);
    return 1;
  }

  if (strcmp(s, "load") == 0) {
    s = strtok(NULL, " ");
    load_file(*hsize, node);
    return 1;
  }

  if (strcmp(s, "undo") == 0) {
    init_canvas();
    Node *temp = node;
    while (temp->next) {
      temp = temp->next;
    }
    node = pop_back(node);
    --hsize;
    Node *p = node;
    while (p) {
      interpret_command(p->str, hsize, p);
      p = p->next;
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
  Node *node = NULL;

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

    const int r = interpret_command(buf, &hsize, node);
    if (r == 2)
      break;
    if (r == 0) {
      node = push_back(node, p_buf);
      hsize++;
    }
    print_canvas(fp);
  }
  fclose(fp);

  return 0;
}
