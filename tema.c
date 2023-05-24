#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Queue.h"
#include "Stack.h"
#include "Tree.h"
#include "Utils.h"

int main(int argc, char* argv[]) {
  FILE *f, *h, *g;
  // Deschidem fisierele din care citim si in care scriem
  h = fopen(argv[1], "r");
  f = fopen(argv[2], "r");
  g = fopen(argv[3], "w");
  // Declaram nodul de inceput al listei
  Node_list *head = NULL, *top_8_teams = NULL;
  Node_tree *tree = NULL;
  int i = 0, nr_teams = 0, j = 0, nr_players = 0, k = 0, points = 0;
  int *op = (int *)malloc(6 * sizeof(int));
  // Citim operatiile din fisierul h si le scriem intr-un vector
  for (i = 1; i <= 5; i++) {
    fscanf(h, "%d ", &op[i]);
  }
  // Citim numarul de echipe din fisierul f
  fscanf(f, "%d", &nr_teams);
  char *s;
  s = malloc(50 * sizeof(char));
  // Verificam care operatii trebuie facute ajutandu-ne de vectorul op
  if (op[1]) {
    // Pentru fiecare echipa vom citi din fisierul f  numele echipei,numarul
    // numarul de jucatori, cele doua nume ale fiecarui jucator si punctajul
    // fiecarui jucator
    for (i = 0; i < nr_teams; i++) {
      fscanf(f, "%d ", &nr_players);
      for (j = 0; j <= nr_players + 1; j++) {
        // Daca sirul citit din fisierul f este numele echipei,
        // atunci ne aflam la pasul j = 0
        if (j == 0) {
          fgets(s, 50, f);
          // Eliminam caracterul de spatiu de la finalul sirului, daca exista
          // int k = 0;
          // for (k = 0; k <= strlen(s); k++) {
          //   printf("%d ", s[k]);
          // }
          // printf("\n");
          if (s[strlen(s) - 3] == ' ') {
            s[strlen(s) - 1] = '\0';
          }
          s[strlen(s)-2] = '\0';
          // Adaugam echipa la inceputul listei
          addAtBeginning(&head, s, strlen(s), nr_players);
        } else {
          fgets(s, 50, f);
          if (s[1] != '\n') {
            // Eliminam linia noua dintre echipe
            if (s[strlen(s) - 1] == '\n') {
              s[strlen(s) - 2] = '\0';
            }
            // Sirul citit contine cele doua nume si punctajul unui jucator,
            // prin urmare folosim functia strtok pentru a desparti cuvintele
            char *p, cuvant[50];
            int nr = 0;
            p = strtok(s, " ");
            while (p != NULL) {
              strcpy(cuvant, p);
              if (nr == 0) {
                strcpy(head->player[j-1].firstName, cuvant);
              } else {
                if (nr == 1) {
                  strcpy(head->player[j-1].secondName, cuvant);
                } else {
                  // Folosind functia atoi convertim punctajul din char in int
                  head->player[j-1].points = atoi(cuvant);
                }
              }
              nr++;
              p = strtok(NULL, " ");
            }
          }
        }
      }
    }
    if (!op[2]) {
      print_teams(head, g);
    }
  }
  if (op[2]) {
    // Calculam numarul total de puncte al fiecarei echipe
    team_points(head, nr_players);
    int nr;
    float min = minim(head);
    nr = power_of_2(nr_teams);
    // Stergem echipele cu cele mai mici punctaje conform cerintei
    while (nr < nr_teams) {
      head = deleteOnce(head, min);
      min = minim(head);
      nr_teams--;
    }
    // Afisam echipele ramase in lista
    print_teams(head, g);
  }
  if (op[3]) {
    int round = 1, size = 0, ok = 1;
    Queue *matches = createQueue();
    Node_stack *winners = NULL, *losers = NULL;
    Node_list *p;
    while (ok == 1) {
      p = head;
      size = 0;
      // Punem in coada cu meciuri echipele si punctajele lor
      while (p != NULL) {
        enQueue(matches, &p, &(p->next));
        p = p->next;
        p = p->next;
        size++;
      }
      fprintf(g, "\n");
      if (head != NULL) {
        free_list(&head, nr_players);
      }
      head = NULL;
      // Scriem coada cu meciuri in fisier
      printQueue(matches, round, g);
      Node_queue *q;
      q = matches->front;
      // Punem in stivele winners si losers echipele invingatoare
      // si echipele invinse
      while (q != NULL) {
        if (compare_points(q->points_1, q->points_2) > 0) {
          push(&winners, q->team_1, q->points_1, 1);
          push(&losers, q->team_2, q->points_2, 0);
          addAtBeginning(&head, q->team_1, strlen(q->team_1), nr_players);
          head->points = winners->points;
        } else {
          push(&winners, q->team_2, q->points_2, 1);
          push(&losers, q->team_1, q->points_1, 0);
          addAtBeginning(&head, q->team_2, strlen(q->team_2), nr_players);
          head->points = winners->points;
        }
        q = q->next;
      }
      // Daca am ajuns la 8 echipe castigatoare, le bagam intr-o lista
      if (size == 8) {
        Node_stack *s;
        s = winners;
        while (s != NULL) {
          addAtBeginning(&top_8_teams, s->team_name, strlen(s->team_name), nr_players);
          top_8_teams->points = s->points;
          s = s->next;
        }
      }
      fprintf(g, "\n");
      // Scriem in fisier echipele din stiva de invingatori,
      // urmate de punctajul lor
      print_stack(winners, round, g);
      round++;
      // Eliberam memoria pentru coada de meciuri
      if (matches != NULL) {
        free_queue(matches);
      }
      matches = createQueue();
      // Eliberam memoria pentru cele doua stive
      if (winners != NULL) {
        deleteStack(&winners);
      }
      winners = NULL;
      if (losers != NULL) {
        deleteStack(&losers);
      }
      losers = NULL;
      if (size == 1) {
        ok = 0;
      }
    }
    // Eliberam memoria pentru coada de meciuri
    free_queue(matches);
  }
  if (op[4]) {
    // Initializam arborele si adaugam prima echipa din lista
    initTree(&tree, top_8_teams->team_name, top_8_teams->points);
    Node_list *p = top_8_teams->next;
    // Adaugam restul de echipe intr-un arbore de tip BST
    while (p != NULL) {
      insert(tree, p->team_name, p->points);
      p = p->next;
    }
    // Scriem in fisier arborele de la dreapta la stanga(descrescator)
    fprintf(g, "\nTOP 8 TEAMS:\n");
    print_tree(tree, g);
  }
  if (op[5]) {
    fprintf(g, "\nTHE LEVEL 2 TEAMS ARE: \n");
    fprintf(g , "\n");
    // Eliberam memoria pentru arborele de la operatia 4
    free_tree(tree);
    tree = NULL;
    Node_list *p = top_8_teams;
    // Adaugam cele 8 echipe din lista intr-un arbore de tip AVL
    while (p != NULL) {
    tree = insert_AVL(tree, p->team_name, p->points);
    p = p->next;
    }
    // Afisam echipele de pe nivelul doi al arborelui
    print_level2(tree, g);
  }
  // Eliberam memoria pentru toate variabilele alocate dinamic
  free(s);
  free(op);
  free_list(&head, nr_players);
  free_list(&top_8_teams, nr_players);
  free_tree(tree);
  // Inchidem fisierele
  fclose(h);
  fclose(f);
  fclose(g);
  return 0;
}