#ifndef RESTAURANT_H
#define RESTAURANT_H

#define MAX_NAME 50

typedef struct Party {
    char name[MAX_NAME];
    int size;
    struct Party *next;
} Party;

typedef struct Table {
    int id;
    int capacity;
    int occupied;
    char occupant[MAX_NAME];
    struct Table *left;
    struct Table *right;
} Table;

typedef struct {
    Party *front;
    Party *rear;
} Waitlist;

void initWaitlist(Waitlist *list);
void addParty(Waitlist *list, const char *name, int size);
void seatNextParty(Waitlist *list, Table *root);
void viewWaitlist(const Waitlist *list);
void estimateWaitTime(const Waitlist *list);
void cancelReservation(Waitlist *list, const char *name);
void prioritizeVIP(Waitlist *list, const char *name);
void freeWaitlist(Waitlist *list);

Table* insertTable(Table *root, int id, int capacity);
Table* findSuitableTable(Table *root, int size);
void inorder(Table *root);
void freeTree(Table *root);
void freeTableById(Table *root, int id);

#endif