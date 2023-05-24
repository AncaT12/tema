#pragma once
#include "Utils.h"

// Definim structura pentru nodul arborelui

struct N {
  char *team_name; // numele echipei
  float points; // numarul total de puncte al echipei
  int height; // inaltimea arborelui
  struct N *left, *right; // legatura catre subarborii din stanga si dreapta
};

typedef struct N Node_tree;

// Functia height calculeaza inaltimea unui nod din arbore

int height(Node_tree *root) {
  int hs = 0, hd = 0;
  if (root == NULL) {
    return -1;
  }
  // Inaltimea subarborelui stang
  hs = height(root->left);
  // Inaltimea subarborelui drept
  hd = height(root->right);
  // Returneaza inaltimea nodului
  return 1 + ((hs > hd) ? hs : hd );
}

// Functia initTree aloca memorie pentru un arbore si
// ii initializeaza radacina

void initTree(Node_tree **root, char *name, float points) {
  // Alocam dinamic memorie pentru radacina arborelui
  *root = (Node_tree *)malloc(sizeof(Node_tree));
  // Alocam memorie pentru numele echipei
  (*root)->team_name = (char *)malloc(50 * sizeof(char));
  strcpy((*root)->team_name, name);
  (*root)->points = points;
  (*root)->left = (*root)->right = NULL;
}

// Functia newNode aloca memorie pentru un nod al arborelui
// si il initializeaza

Node_tree* newNode(char *name, float points) {
  // Alocam memorie pentru un nod al arborelui
  Node_tree *node = (Node_tree *)malloc(sizeof(Node_tree));
  // Alocam memorie pentru numele echipei
  node->team_name = (char *)malloc(50 * sizeof(char));
  strcpy(node->team_name, name);
  node->points = points;
  node->left = node->right = NULL;
  return node;
}

// Functia insert insereaza un nod in arbore astfel incat
// acesta sa fie arbore binar de cautare

Node_tree* insert(Node_tree *node, char *name, float points) {
  // Daca nu exista radacina, atunci vom crea un nou nod
  if (node == NULL) {
    return newNode(name, points);
  }
  // Altfel, facem verificarile necesare pentru ca arborele
  // sa-si pastreze proprietatea de BST
  if (points < node->points) {
    node->left = insert(node->left, name, points);
  } else {
    if (points > node->points) {
      node->right = insert(node->right, name, points);
    } else {
      if (strcasecmp(name, node->team_name) > 0) {
        node->right = insert(node->right, name, points);
      } else {
        node->left = insert(node->left, name, points);
      }
    }
  }
  return node;
}

// Functia print_tree afiseaza arborele de la dreapta la stanga(descrescator)

void print_tree(Node_tree *root, FILE *g) {
  if (root) {
    print_tree(root->right, g);
    fprintf(g, "%-34s-  %.2lf\n", root->team_name, root->points);
    print_tree(root->left, g);
  }
}

// Functia free_tree elibereaza memoria alocata pentru arbore

void free_tree(Node_tree *root) {
  if (root == NULL) {
    return;
  }
  if (root->left == NULL && root->right == NULL) {
    free(root->team_name);
    free(root);
    return;
  }
  free_tree(root->left);
  free_tree(root->right);
}

// Functia RightRotation face o rotatie la dreapta

Node_tree* RightRotation(Node_tree *z) {
  Node_tree *y = z->left;
  Node_tree *T3 = y->right;
  // Roteste
  y->right = z;
  z->left = T3;
  // Modifica inaltimile pentru z si y
  z->height = maxim(height(z->left), height(z->right)) + 1;
  y->height = maxim(height(y->left), height(y->right)) + 1;
  // y este noua radacina
  return y;
}

// Functia LeftRotation face o rotatie la stanga

Node_tree* LeftRotation(Node_tree *z) {
  Node_tree *y = z->right;
  Node_tree *T2 = y->left;
  // Roteste
  y->left = z;
  z->right = T2;
  // Modifica inaltimile pentru z si y
  z->height = maxim(height(z->left), height(z->right)) + 1;
  y->height = maxim(height(y->left), height(y->right)) + 1;
  // y este noua radacina
  return y;
}

// Functia LRRotation face o rotatie stanga-dreapta

Node_tree* LRRotation(Node_tree *Z) {
  Z->left = LeftRotation(Z->left);
  return RightRotation (Z);
}

// Functia RLRotation face o rotatie dreapta-stanga

Node_tree* RLRotation(Node_tree *Z) {
  Z->right = RightRotation(Z->right);
  return LeftRotation (Z);
}

// Functia balance_factor calculeaza factorul de balans

int balance_factor(Node_tree *node) {
  if (node == NULL) {
    return 0;
  }
  return height(node->left) - height(node->right);
}

// Functia print_level2 scrie in fisier elementele de pe
// nivelul doi al arborelui

void print_level2(Node_tree *root, FILE *g) {
  Node_tree *left_tree = root->left, *right_tree = root->right;
  if (left_tree != NULL) {
    if (left_tree->left != NULL) {
      fprintf(g, "%s\n", left_tree->left->team_name);
    }
    if (left_tree->right != NULL) {
      fprintf(g, "%s\n", left_tree->right->team_name);
    }
  }
  if (right_tree != NULL) {
    if (right_tree->left != NULL) {
      fprintf(g, "%s\n", right_tree->left->team_name);
    }
    if (right_tree->right != NULL) {
      fprintf(g, "%s\n", right_tree->right->team_name);
    }
  }
}

// Functia compare_nodes compara doua noduri ale arborelui

int compare_nodes(Node_tree *node_1, Node_tree *node_2) {
  if (node_1->points == node_2->points) {
    if (node_1->team_name != NULL && node_2->team_name != NULL) {
      return strcasecmp (node_2->team_name, node_1->team_name);
    }
  }
  return node_1->points - node_2->points;
}

// Functia insert_AVL insereaza in arbore un nod, astfel incat acesta
// sa ramana binar de cautare si echilibrat

Node_tree* insert_AVL(Node_tree *root, char *name, int points) {
  // Daca nu exista radacina, atunci vom crea un nou nod
  if (root == NULL) {
    root = newNode(name, points);
    return root;
  }
  // Altfel, facem verificarile necesare pentru ca arborele
  // sa-si pastreze proprietatea de AVL
  Node_tree *node = newNode (name, points);
  int compare = compare_nodes(root, node);
  if (compare > 0) {
    root->left =  insert_AVL(root->left, name, points);
  } else {
    root->right = insert_AVL(root->right, name, points);
  }
  root->height = maxim(height(root->left), height(root->right)) + 1;
  int bal_fac = balance_factor(root);
  if (bal_fac > 1) {
    if (compare < 0) {
      root->left = LeftRotation(root->left);
    }
    return RightRotation(root);
  }
  if (bal_fac < -1) {
    if (compare > 0) {
      root->right = RightRotation(root->right);
    }
    return LeftRotation(root);
  }
  return root;
}