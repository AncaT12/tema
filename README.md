Mentionez ca pe checker-ul local primesc 79 de puncte din cele 100.

Programul este format din 4 headere, List.h, Queue.h, Stack.h, Tree.h
si Utils.h, si un cod sursa tema.c

List.h contine structurile Player, Team si functiile necesare pentru
operatiile cu liste.
Structura Player contine informatii despre jucatorii echipei. Aceasta
structura retine primul si al doilea nume ale jucatorilor si punctajul lor.
Structura Team contine informatii despre fiecare echipa. Aceasta structura
retine numele echipei, jucatorii echipei, punctajul total al echipei si
legatura catre urmatoarea echipa. Punctajul total al echipei este calculat
prin media aritmetica a tuturor jucatorilor echipei.
Functia addAtBeginning aloca memorie pentru o noua echipa si pentru fiecare
jucator al echipei si il adauga la inceputul listei ce contine toate echipele.
Functia print_teams scrie intr-un fisier numele tuturor echipelor ce se afla
intr-o lista data.
Functia team_points calculeaza punctajul total al echipei prin media aritmetica
a tuturor punctajelor jucatorilor.
Functia deleteOnce sterge un element dat dintr-o lista.
Functia free_list elibereaza memoria alocata dinamic pentru o lista.

Queue.h continue structurile Q, Elem_q si functiile necesare pentru operatiile
cu cozi.
Structura Elem_q contine informatii despe meciuri: numele celor doua echipe
particpante, punctajele lor si legatura catre urmatorul meci.
Structura Q contine pointeri catre inceputul si finalul cozii.
Functia createQueue aloca memorie pentru o coada.
Functia enQueue aloca memorie pentru un nou meci si il adauga in coada. 
Functia printQueue scrie intr-un fisier numarul rundei si meciurile dintr-o
coada.
Funcia free_queue elibereaza memoria ce a fost alocata pentru o coada.

Stack.h contine structura Elem_s si functiile necesare pentru operatiile cu
stive.
Structura Elem_s contine informatii despre o echipa: nume echipei, punctajul
echipei si legatura catre urmatoarea echipa.
Functia push aloca memorie pentru un element si il adauga in stiva.
Functia print_stack scrie intr-un fisier numarul rundei si echipele castigatoare
din acea runda.
Functia deleteStack elibereaza memoria ce a fost alocata pentru o stiva.

Tree.h contine structura N si funtiile necesare pentru operatiile cu arbori.
Structura N contine informatii despre un nod al unui arbore: numele echipei,
punctajul echipei, inaltimea arborelui si copiii stanga si dreapta.
Functia height calculeaza inaltimea unui nod din arbore.
Functia initTree aloca memorie pentru un arbore si ii initializeaza radacina.
Functia newNode aloca memorie pentru un nod al arborelui si il initializeaza.
Functia insert insereaza un nod in arbore astfel incat acesta sa fie arbore
binar de cautare.
Functia print_tree afiseaza arborele de la dreapta la stanga(descrescator).
Functia free_tree elibereaza memoria alocata pentru un arbore.
Functia RightRotation face o rotatie la dreapta a arborelui.
Functia LeftRotation face o rotatie la stanga a arborelui.
Functia LRRotation face o rotatie stanga-dreapta a arborelui.
Functia RLRotation face o rotatie dreapta-stanga a arborelui.
Functia balance_factor calculeaza factorul de balans al arborelui.
Functia print_level2 scrie in fisier elementele de pe
nivelul doi al arborelui.
Functia compare_nodes compara doua noduri ale arborelui.
Functia insert_AVL insereaza in arbore un nod in arbore, astfel incat acesta
sa ramana binar de cautare si echilibrat.


Utils.h contine alte functii pe care le folosim in decursul programului: minim,
power_of_2, compare_points si maxim.
Functia minim calcueaza minimul de puncte si il returneaza 
Functia power_of_2 calculeaza cea mai mare putere a lui 2 mai mica sau egala cu
un numar natural n.
Functia compare_points compara punctajele a doua echipa, urmand sa returneze o
valoare pozitiva daca prima echipa este castigatoare si o valoare negativa daca
a doua echipa este castigatoare.
Functia maxim calculeaza maximul dintre doua numere.

tema.c contine implementarea functiilor cerute in enuntul problemei.
Se deschid fisierele si se citesc din acestea operatiile ce trebuie facute si
echipele. Operatiile vor fi retinute intr-un vector numit op, iar echipele vor
fi bagate intr-o lista simplu inlantuita.
Se verifica apoi ce operatii trebuie facute si se implementeaza cerintele:
Pentru operatia 1 vom citi din fisier echipele si jucatorii si le vom retine
intr-o lista. Daca nu trebuie facuta si operatia doi, atunci vom scrie intr-un
fisier toate echipele din lista.
Pentru operatia 2 vom modifica lista astfel incat sa ramanem cu 2^p echipe,
unde 2^p este cea mai mare putere a lui 2 mai mica decat numarul de echipe.
Echipele cu cel mai mic punctaj vor fi eliminate, iar apoi in fisier se vor
scrie echipele ramase in lista.
Pentru operatia trei se va face o coada de meciuri in care vom stoca meciurile
dintre echipe. Pentru fiecare meci vom adauga in stiva winners echipa
invingatoare si in stiva losers echipa invinsa.De altfel, echipele castigatoare
vor fi adaugate in lista, urmand ca dupa aceea sa le bagam intr-o noua coada.
Vom repeta aceste operatii pana cand ajungem la un singur invingator. De altfel,
cand stiva winners va contine doar 8 echipe acestea vor fi retinute in lista
top_8_teams.
Pentru operatia 4 vom pune intr-un arbore toate echipele din lista top_8_teams,
avand grija ca atunci cand le inseram sa obtinem un arbore BST. Dupa aceea vom
scrie intr-un fisier echipele din arbore de la dreapta la stanga(descrescator).
Pentru operatia 5 vom pune intr-un arbore toate echipele din lista top_8_teams,
avand grija ca atunci cand le inseram sa obtinem un arbore AVL. Dupa aceea vom
scrie intr-un fisier echipele ce se afla pe al doilea nivel al arborelui.