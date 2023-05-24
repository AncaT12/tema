#pragma once

// Definim structura pentru jucatori

struct Player {
  char *firstName; // primul nume al jucatorului
  char *secondName; // al doilea nume al jucatorului
  int points; // punctajul pe care il are jucatorul
};

// Definim structura pentru echipe

struct Team {
  char *team_name; // numele echipei
  struct Player *player; // vector de tip Player care retine toti jucatorii
  float points; // punctajul total al echipei
  struct Team *next; // pointer catre urmatoarea echipa din lista
};

typedef struct Team Node_list;

// Functia addAtBeginning adauga un nou nod la inceputul unei liste

void addAtBeginning(Node_list **team, char *string, int nr_char, int nr_players) {
  // Declaram un nod de tip lista si alocam memorie pentru el
  Node_list *newNode = (Node_list *)malloc(sizeof(Node_list));
  // Alocam memorie pentru numele echipei
  newNode->team_name = malloc((nr_char + 1) * sizeof(char));
  strcpy(newNode->team_name, string);
  newNode->player = malloc(nr_players * sizeof(struct Player));
  // Alocam memorie pentru numele fiecarui jucator
  int i = 0;
  for (i = 0; i < nr_players; i++) {
    newNode->player[i].firstName = malloc(50 * sizeof(char));
    newNode->player[i].secondName = malloc(50 * sizeof(char));
  }
  newNode->next = *team;
  newNode->points = 0;
  *team = newNode;
}

// Functia print_teams scrie intr-un fisier numele tuturor echipelor din lista

void print_teams(Node_list *head, FILE *g) {
  Node_list *p;
  p = head;
  while (p != NULL) {
    fprintf(g, "%s\n", p->team_name);
    p = p->next;
  }
  // fprintf(g,"\n");
}

// Functia team_points calculeaza punctajul total al unei echipe

void team_points(Node_list *head, int nr_players) {
  int i = 0;
  Node_list *p;
  p = head;
  // Facem media aritmetica a punctajelor tuturor jucatorilor dintr-o echipa
  while (p != NULL) {
    for (i = 0; i < nr_players; i++) {
      p->points = p->points + p->player[i].points;
    }
    p->points = p->points / nr_players;
    p = p->next;
  }
}

// Functia deleteOnce sterge un element dat dintr-o lista

Node_list* deleteOnce(Node_list *p, float elem) {
  Node_list *ant = p;
  Node_list *cp = p;
  int ok = 1;
  // Verificam daca elementul este pe prima pozitie
  if (p->points == elem) {
    return p->next;
  }
  // Cazul general
  while (p != NULL && ok) {
    ant = p;
    p = p->next;
    if (p->points == elem) {
      ant->next = p->next;
      ok = 0;
    }
    // p = p->next;
  }
  return cp;
}

// Functia free_list elibereaza memoria listei

void free_list(Node_list **team, int nr_players) {
  Node_list *copy;
  while (*team != NULL) {
    copy = (*team)->next;
    // Eliberam memoria pentru numele fiecarui jucator al unei echipe
    for (int i = 0; i < nr_players; i++) {
      free((*team)->player[i].firstName);
      free((*team)->player[i].secondName);
    }
    // Eliberam memoria pentru numele echipei
    free((*team)->team_name);
    // Eliberam memoria pentru vectorul de jucatori ai echipei
    free((*team)->player);
    free(*team);
    *team = copy;
  }
  *team = NULL;
}