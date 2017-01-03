#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 70
#define HEIGHT 40

#define MAX_HISTORY 100
#define BUFSIZE 1000

struct node {
  char *str;
  struct node *next;
};

struct rgb {
  int R;
  int G;
  int B;
};

typedef struct node Node;
typedef struct rgb RGB;

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

// This method for debugging.
void print_all_node(Node *head) {
  while (head) {
    printf("%s", head->str);
    head = head->next;
  }
}

// This is globale variables used in this program.
Node *canceled_command;
char canvas[WIDTH][HEIGHT];
int color_canvas[WIDTH][HEIGHT] = {{0}};
int color_num;
int bg_color_num = 40;
int snow_count;

// Methods for manipulating colors.
int convert_color_name_to_color_num(const char *color_name) {
  if (!strcmp(color_name, "black"))
    return 30;
  if (!strcmp(color_name, "red"))
    return 31;
  if (!strcmp(color_name, "green"))
    return 32;
  if (!strcmp(color_name, "yellow"))
    return 33;
  if (!strcmp(color_name, "yellow"))
    return 33;
  if (!strcmp(color_name, "blue"))
    return 34;
  if (!strcmp(color_name, "magenta"))
    return 35;
  if (!strcmp(color_name, "cyan"))
    return 36;
  return 0;
}

RGB *make_rgb(int color_num) {
  RGB *rgb = malloc(sizeof(RGB));
  if (color_num == 30) {
    rgb->R = 0;
    rgb->G = 0;
    rgb->B = 0;
  }
  if (color_num == 31) {
    rgb->R = 255;
    rgb->G = 0;
    rgb->B = 0;
  }

  if (color_num == 32) {
    rgb->R = 0;
    rgb->G = 128;
    rgb->B = 0;
  }

  if (color_num == 33) {
    rgb->R = 255;
    rgb->G = 255;
    rgb->B = 0;
  }
  if (color_num == 34) {
    rgb->R = 0;
    rgb->G = 0;
    rgb->B = 255;
  }
  if (color_num == 35) {
    rgb->R = 255;
    rgb->G = 0;
    rgb->B = 255;
  }
  if (color_num == 36) {
    rgb->R = 0;
    rgb->G = 255;
    rgb->B = 255;
  }
  if (color_num == 37) {
    rgb->R = 255;
    rgb->G = 255;
    rgb->B = 255;
  }

  if (color_num == 37) {
    rgb->R = 0;
    rgb->G = 0;
    rgb->B = 0;
  }
  return rgb;
}

void set_color_num(const char *color_name) {
  color_num = convert_color_name_to_color_num(color_name);
}

void set_bgcolor_num(const char *color_name) {
  bg_color_num = 10 + convert_color_name_to_color_num(color_name);
}

void add_char_color(FILE *fp, char c, int color_num) {
  switch (color_num) {
  case 31:
    fputs("\x1b[31m", fp);
    fputc(c, fp);
    break;
  case 32:
    fputs("\x1b[32m", fp);
    fputc(c, fp);
    break;
  case 33:
    fputs("\x1b[33m", fp);
    fputc(c, fp);
    break;
  case 34:
    fputs("\x1b[34m", fp);
    fputc(c, fp);
    break;
  case 35:
    fputs("\x1b[35m", fp);
    fputc(c, fp);
    break;
  case 36:
    fputs("\x1b[36m", fp);
    fputc(c, fp);
    break;
  case 37:
    fputs("\x1b[37m", fp);
    fputc(c, fp);
    break;
  }
}

void change_bg_color(FILE *fp) {
  switch (bg_color_num) {
  case 40:
    fputs("\x1b[40m", fp);
    break;
  case 41:
    fputs("\x1b[41m", fp);
    break;
  case 42:
    fputs("\x1b[42m", fp);
    break;
  case 43:
    fputs("\x1b[43m", fp);
    break;
  case 44:
    fputs("\x1b[44m", fp);
    break;
  case 45:
    fputs("\x1b[45m", fp);
    break;
  case 46:
    fputs("\x1b[46m", fp);
    break;
  }
}

const char *default_history_file = "history.txt";
int interpret_command(const char *command, int *hsize, Node *node);

void print_canvas(FILE *fp) {
  int x, y;

  fprintf(fp, "----------\n");

  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
      const char c = canvas[x][y];
      change_bg_color(fp);
      if (canvas[x][y] != ' ') {
        add_char_color(fp, c, color_canvas[x][y]);
      } else {
        fputc(c, fp);
      }
    }
    fputc('\n', fp);
  }
  fflush(fp);
}

void init_canvas() { memset(canvas, ' ', sizeof(canvas)); }

int max(const int a, const int b) { return (a > b) ? a : b; }

void add_color_code(int x, int y) {
  if (color_num != 0) {
    color_canvas[x][y] = color_num;
  } else {
    color_canvas[x][y] = 37; // if the color is till default one(white), it set
                             // the color code to 37, which represnts white
                             // color.
  }
}
// Commands for drawing
void draw_line(const int x0, const int y0, const int x1, const int y1) {
  int i;
  const int n = max(abs(x1 - x0), abs(y1 - y0));
  for (i = 0; i <= n; i++) {
    const int x = x0 + i * (x1 - x0) / n;
    const int y = y0 + i * (y1 - y0) / n;
    canvas[x][y] = '#';
    add_color_code(x, y);
  }
}

void draw_rect(const int x0, const int y0, const int width, const int height) {
  draw_line(x0, y0, x0 + width, y0);
  draw_line(x0 + width, y0, x0 + width, y0 + height);
  draw_line(x0, y0, x0, y0 + height);
  draw_line(x0, y0 + height, x0 + width, y0 + height);
};

void draw_rect_fill(const int x0, const int y0, const int width,
                    const int height) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (x >= x0 && y >= y0 && x < x0 + width && y < y0 + height) {
        canvas[x][y] = '#';
        add_color_code(x, y);
      }
    }
  }
}

void draw_circle(const int x0, const int y0, const int r, const int fillout) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (fillout) {
        if (fabs(pow((x - x0 / 2), 2) + pow((y - y0 / 2), 2)) < r * r / 4) {
          canvas[x][y] = '#';
          add_color_code(x, y);
        }
      } else {
        if (fabs(pow((x - x0 / 2), 2) + pow((y - y0 / 2), 2) - r * r / 4) <
            (r / 2)) {
          canvas[x][y] = '#';
          add_color_code(x, y);
        }
      }
    }
  }
}

void draw_triangle(const int x0, const int y0, const int x1, const int y1,
                   const int x2, const int y2) {
  int a = sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
  int b = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
  int c = sqrt(pow(x2 - x0, 2) + pow(y2 - y0, 2));
  if (a + b > c && b + c > a && c + a > b) {
    draw_line(x0, y0, x1, y1);
    draw_line(x1, y1, x2, y2);
    draw_line(x2, y2, x0, y0);
  } else {
    printf("you cannot write an triangle with those inputs values.");
  }
}

void add_snow_effect() {
  srand((unsigned)time(NULL));
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (canvas[x][y] != '#') {
        canvas[x][y] = (rand() % 20 == 1) ? '*' : ' ';
        color_canvas[x][y] = (color_canvas[x][y]) ? color_canvas[x][y] : 37;
      }
    }
  }
  snow_count++;
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

void save_as_pbm() {
  FILE *fp;
  if ((fp = fopen("canvas.pbm", "w")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", "canvas.pbm");
    return;
  }
  fputs("P1\n", fp);
  fprintf(fp, "%d %d\n", WIDTH, HEIGHT);
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (canvas[x][y] == '#') {
        fputc('1', fp);
      } else {
        fputc('0', fp);
      }
      if (x != WIDTH - 1) {
        fputc(' ', fp);
      }
    }
    fputc('\n', fp);
  }
  fclose(fp);
}

void save_command(char *name, int command_size, Node *node) {
  FILE *fp;
  if ((fp = fopen("command.txt", "w")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", "canvas.ppm");
    return;
  }
  fputs(name, fp);
  fputc('\n', fp);
  for (int i = 0; i < command_size; i++) {
    Node *p = node;
    while (p->next) {
      p = p->next;
    }
    printf("%s", node->str);
    fputs(node->str, fp);
    node = pop_back(node);
  }
  fclose(fp);
  print_all_node(node);
}

void load_command(char *name) {}

void save_as_ppm() {
  FILE *fp1;
  if ((fp1 = fopen("canvas.ppm", "w")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", "canvas.ppm");
    return;
  }

  RGB *rgb;
  fputs("P6\n", fp1);
  fprintf(fp1, "%d %d\n", WIDTH, HEIGHT);
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (canvas[x][y] == '#') {
        rgb = make_rgb(color_canvas[x][y]);
        fprintf(fp1, "%d %d %d", rgb->R, rgb->G, rgb->B);
      } else {
        rgb = make_rgb(30);
        fprintf(fp1, "%d %d %d", rgb->R, rgb->G, rgb->B);
      }
      if (x != WIDTH - 1) {
        fputc(' ', fp1);
      }
    }
    fputc('\n', fp1);
  }
  fclose(fp1);
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

  if (strcmp(s, "rect_fill") == 0) {
    int x0, y0, width, height;
    x0 = atoi(strtok(NULL, " "));
    y0 = atoi(strtok(NULL, " "));
    width = atoi(strtok(NULL, " "));
    height = atoi(strtok(NULL, " "));
    draw_rect_fill(x0, y0, width, height);
    return 0;
  }

  if (strcmp(s, "circle") == 0) {
    int x0, y0, r;
    x0 = atoi(strtok(NULL, " "));
    y0 = atoi(strtok(NULL, " "));
    r = atoi(strtok(NULL, " "));
    draw_circle(x0, y0, r, 0);
    return 0;
  }

  if (strcmp(s, "circle_fill") == 0) {
    int x0, y0, r;
    x0 = atoi(strtok(NULL, " "));
    y0 = atoi(strtok(NULL, " "));
    r = atoi(strtok(NULL, " "));
    draw_circle(x0, y0, r, 1);
    return 0;
  }

  if (strcmp(s, "tri") == 0) {
    int x0, y0, x1, y1, x2, y2;
    x0 = atoi(strtok(NULL, " "));
    y0 = atoi(strtok(NULL, " "));
    x1 = atoi(strtok(NULL, " "));
    y1 = atoi(strtok(NULL, " "));
    x2 = atoi(strtok(NULL, " "));
    y2 = atoi(strtok(NULL, " "));
    draw_triangle(x0, y0, x1, y1, x2, y2);
    return 0;
  }

  if (strcmp(s, "color") == 0) {
    set_color_num(strtok(NULL, " "));
    return 0;
  }

  if (strcmp(s, "bgcolor") == 0) {
    set_bgcolor_num(strtok(NULL, " "));
    return 0;
  }

  if (strcmp(s, "snow") == 0) {
    snow_count++;
    add_snow_effect();
    return 0;
  }

  if (strcmp(s, "save") == 0) {
    s = strtok(NULL, " ");
    save_history(s, *hsize, node);
    return 1;
  }

  if (strcmp(s, "savecommand") == 0) {
    char command_name[20];
    strcpy(command_name, strtok(NULL, " "));
    int command_size = atoi(strtok(NULL, " "));
    save_command(command_name, command_size, node);
    return 1;
  }
  if (strcmp(s, "savepbm") == 0) {
    save_as_pbm();
    return 1;
  }
  if (strcmp(s, "saveppm") == 0) {
    save_as_ppm();
    return 1;
  }

  if (strcmp(s, "load") == 0) {
    s = strtok(NULL, " ");
    node = load_file(*hsize, node);
    return 1;
  }

  if (strcmp(s, "undo") == 0) {
    init_canvas();
    Node *temp = node;
    while (temp->next) {
      temp = temp->next;
    }
    canceled_command = push_front(canceled_command, temp->str);
    node = pop_back(node);
    --hsize;
    Node *p = node;
    while (p) {
      interpret_command(p->str, hsize, p);
      p = p->next;
    }
    return 1;
  }

  if (strcmp(s, "redo") == 0) {
    if (canceled_command) {
      interpret_command(canceled_command->str, hsize, canceled_command);
      node = push_back(node, canceled_command->str);
      hsize++;
      canceled_command = pop_front(canceled_command);
    } else {
      printf("There are no commands to redo.");
    }
    return 1;
  }

  if (strcmp(s, "quit") == 0) {
    return 2;
  }
  printf("error: unknown command.\n");

  return 1;
}

void show_help() {
  printf("------------------------\n");
  printf("Welcome to CUIPalette!");
  FILE *fp;
  fp = fopen("help.txt", "r");
  char line[200];
  while (fgets(line, sizeof(line), fp) != NULL) {
    printf("%s", line);
  }
  fclose(fp);
  printf("------------------------\n");
}

int main() {
  const char *filename = "canvas.txt";
  FILE *fp;
  char buf[BUFSIZE];
  char *p_buf;
  Node *node = NULL;
  color_num = 0;
  bg_color_num = 0;
  snow_count = 0;

  if ((fp = fopen(filename, "a")) == NULL) {
    fprintf(stderr, "error: cannot open %s.\n", filename);
    return 1;
  }
  show_help();

  init_canvas();
  print_canvas(fp);

  int hsize = 0;
  while (1) {

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
    if (snow_count) {
      for (int i = 0; i < 10; i++) {
        add_snow_effect();
        sleep(1);
        print_canvas(fp);
      }
      snow_count = 0;
    }
  }
  fclose(fp);

  return 0;
}
