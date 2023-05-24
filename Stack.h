#pragma once

// Definim structura pentru un nod al stivei

struct Elem_s {
  char *team_name; // numele echipei
  float points; // punctajul echipei
  struct Elem_s *next; // pointer catre urmatoarea echipa din stiva
};

typedef struct Elem_s Node_stack;

// Functia push adauga elemente in stiva

void push(Node_stack **top , char *name, float points, int win) {
  Node_stack *newNode = (Node_stack *)malloc(sizeof(Node_stack));
  // Alocam memorie pentru numele echipei
  newNode->team_name = (char *)malloc(50 * sizeof(char));
  strcpy(newNode->team_name, name);
  // Calculam noul punctaj al echipei si il adaugam
  newNode->points = points + win;
  newNode->next = *top;
  *top = newNode;
}

// Functia print_stack scrie intr-un fisier invingatorii meciurilor
// dintr-o runda, urmati de punctajele echipei

void print_stack(Node_stack *top, int round, FILE *g) {
  Node_stack *p;
  p = top;
  // Scriem in fisier numarul rundei si mesajul "WINNERS OF ROUND NO:"
  fprintf(g, "WINNERS OF ROUND NO:%d\n", round);
  while (p != NULL) {
    fprintf(g, "%-34s-  %.2lf\n", p->team_name, p->points);
    p = p->next;
  }
  return;
}

// Functia deleteStack elibereaza memorie pentru o stiva

void deleteStack(Node_stack **top) {
    Node_stack* temp;
    while (*top != NULL) {
        temp = *top;
        *top = (*top)->next;
        free(temp->team_name);
        free(temp);
    }
}
