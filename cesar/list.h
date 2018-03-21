#ifndef _LIST_H
#define _LIST_H

//structure
typedef struct list {
int data;
struct list *next_data;
} list;

//profils

list *empty_list();
list *initialisation (int a);
list *insert(int, list*);
void *append(int a, list* l);
void *add(int a, int index, list* l);
void afficher_liste(list*);
void get_tail(list* l);
int length(list* l);
void is_empty(list* l);

#endif
