#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct position {
    int x;
    int y;
};

struct cells {
    int energy;
    char name[256];
    struct position pos;
    int level;
    int energy_limit;
};

struct node {
    struct cells *cell;
    struct node *next;
};


struct Head {
    struct node *head;
    int length;
};

void Make_A_List();

struct cells *Make_A_Cell(struct position pos,char name[256]);

void addFront(struct cells *cell);

void addEnd(struct cells *cell);

void deleteNode(char name[256],struct position pos);

#endif // STRUCT_H_INCLUDED
