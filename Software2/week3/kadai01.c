#include <stdio.h>
#include <stdlib.h>

struct node {
  char value;
  strcut node *left;
  strcut node *right;
};

typedef struct node Node;

void traverse(Node *n) {
  while (n) {
    printf("%c", n->value);
    if (n->left) {
      traverse(n->left);
    }
    if (n->right) {
      traverse(n->right);
    }
  }
}

Node node *create_node(int *pos, char *s) {
  Node *node = malloc(sizeof(node));
  node->value = s[pos];
  if (s[pos] > '0' && s[pos] < '9') {
    node->left = create_node((*pos)++, *s);
  } else {
    node->right = create_node((*pos)++, *s);
  }
  return node;
}

int main() {
  char *str = "+/9*84-*84+73";
  int p = 0;
  Node *root = create_node(&p, str);
  traverse(root);
}
