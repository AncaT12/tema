#pragma once

// Functia minim calcueaza minimul de puncte si il returneaza 

float minim(Node_list *head) {
  Node_list *p;
  p = head;
  float min = p->points;
  p = p->next;
  while (p != NULL) {
    if (p->points < min) {
      min = p->points;
    }
    p = p->next;
  }
  return min;
}

// Functia power_of_2 calculeaza cea mai mare putere
// a lui 2 mai mica sau egala cu un numar natural n

int power_of_2(int n) {
  int nr = 1;
  while (nr < n) {
    nr = nr * 2;
  }
  // Daca numarul calculat depaseste valoarea lui n,
  // este nevoie sa facem o impartire la 2
  if (nr > n) {
    nr = nr / 2;
    return nr;
  }
  return nr;
}

// Functia compare_points compara punctajele a doua echipa, urmand
// sa returneze o valoare pozitiva daca prima echipa este castigatoare
// si o valoare negativa daca a doua echipa este castigatoare

int compare_points(float points1, float points2) {
  if (points1 <= points2) {
    return -1;
  } else {
      return 1;
  }
}

// Functia maxim calculeaza maximul dintre doua numere

int maxim(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}