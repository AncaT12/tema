#pragma once

// Definim structura pentru un nod al cozii

struct Elem_q {
  char *team_1, *team_2; // numele celor doua echipa care participa la meci
  float points_1, points_2; // punctajele celor doua echipe care participa la meci
  struct Elem_q *next; // pointer catre urmatorul meci
};

typedef struct Elem_q Node_queue;

// Definim structura pentru coada

struct Q {
  Node_queue *front, *rear; // pointeri catre nodurile de inceput si de final ale cozii
};

typedef struct Q Queue;

// Functia createQueue aloca memorie pentru o coada

Queue* createQueue() {
  Queue *q;
  q = (Queue *)malloc(sizeof(Queue));
  if (q == NULL) return NULL;
  q->front = q->rear = NULL;
  return q;
}

// Functia enqueue adauga elemente in coada

void enQueue(Queue *q, Node_list **team_1, Node_list **team_2) {
  Node_queue *newNode =( Node_queue *) malloc ( sizeof ( Node_queue ));
  // Alocam memorie pentru numele celor doua echipe care participa la meci
  newNode->team_1 = (char *)malloc((strlen((*team_1)->team_name) + 1) * sizeof(char));
  newNode->team_2 = (char *)malloc((strlen((*team_2)->team_name) + 1) * sizeof(char));
  strcpy(newNode->team_1, (*team_1)->team_name);
  strcpy(newNode->team_2, (*team_2)->team_name);
  // Setam ultimul caracter al numelor pe NULL pentru a scapa de linia noua
  // de la finalul sirurilor de caractere
  // newNode->team_1[strlen((*team_1)->team_name)-2] = '\0';
  // newNode->team_2[strlen((*team_2)->team_name)-2] = '\0';
  newNode->points_1 = (*team_1)->points;
  newNode->points_2 = (*team_2)->points;
  newNode->next = NULL ;
  // Nodurile noi le vom adauga la finalul cozii
  if (q->rear == NULL ) {
    q->rear = newNode;
  } else { // Daca nu exista niciun nod in coada
      (q->rear)->next = newNode;
      (q->rear) = newNode;
    }
  // Daca exita un singur element in coada
  if (q->front == NULL) {
    q->front = q->rear;
  }
}

// Functia printQueue scrie intr-un fisier meciurile dintre echipe
// ce sunt retinute intr-o coada

void printQueue(Queue *q, int round, FILE *g) {
  Node_queue *p;
  p = q->front;
  // Scriem in fisier numarul rundei cu mesajul "--- ROUND NO:"
  fprintf(g, "--- ROUND NO:%d\n", round);
  while (p != NULL) {
    // Scriem in fisier numele echipelor ce participa la meci
    fprintf(g, "%-33s-%33s\n", p->team_1, p->team_2);
    p = p->next;
  }
  return;
}

// Functia free_queue elibereaza memoria pentru coada

void free_queue ( Queue *q) {
  Node_queue * aux ;
  while (q->front != NULL) {
    aux = q->front;
    q->front = q->front->next ;
    free(aux->team_1);
    free(aux->team_2);
    free(aux);
  }
  free (q);
}
