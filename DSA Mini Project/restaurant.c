#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restaurant.h"

void initWaitlist(Waitlist *list) {
    list->front = NULL;
    list->rear = NULL;
}

void addParty(Waitlist *list, const char *name, int size) {
    if (size <= 0) {
        printf("Invalid party size.\n");
        return;
    }

    Party *newNode = (Party*)malloc(sizeof(Party));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return;
    }

    strncpy(newNode->name, name, MAX_NAME - 1);
    newNode->name[MAX_NAME - 1] = '\0';
    newNode->size = size;
    newNode->next = NULL;

    if (list->rear == NULL) {
        list->front = list->rear = newNode;
    } else {
        list->rear->next = newNode;
        list->rear = newNode;
    }

    printf("Party '%s' (size %d) added to waitlist.\n", name, size);
}

void viewWaitlist(const Waitlist *list) {
    if (list->front == NULL) {
        printf("Waitlist is empty.\n");
        return;
    }

    Party *temp = list->front;
    printf("\n--- Current Waitlist ---\n");
    while (temp) {
        printf("%s (size %d)\n", temp->name, temp->size);
        temp = temp->next;
    }
}

void estimateWaitTime(const Waitlist *list) {
    int total = 0;
    Party *temp = list->front;
    while (temp) {
        total += temp->size * 5;
        temp = temp->next;
    }
    printf("Estimated wait time: %d minutes.\n", total);
}

void cancelReservation(Waitlist *list, const char *name) {
    if (list->front == NULL) {
        printf("Waitlist is empty. Cannot cancel.\n");
        return;
    }

    Party *temp = list->front;
    Party *prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Party '%s' not found in waitlist.\n", name);
        return;
    }

    if (prev == NULL) {
        list->front = temp->next;
    } else {
        prev->next = temp->next;
    }

    if (temp == list->rear) {
        list->rear = prev;
    }

    printf("Party '%s' (size %d) has canceled.\n", temp->name, temp->size);
    free(temp);
}

void prioritizeVIP(Waitlist *list, const char *name) {
    if (list->front == NULL) {
        printf("Waitlist is empty.\n");
        return;
    }

    Party *curr = list->front;
    Party *prev = NULL;

    
    while (curr != NULL && strcmp(curr->name, name) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Party '%s' not found.\n", name);
        return;
    }

    
    if (prev == NULL) {
        printf("Party '%s' is already at the front or in VIP order.\n", name);
        return;
    }

    
    prev->next = curr->next;
    if (curr == list->rear) {
        list->rear = prev;
    }


    Party *vipTail = list->front;
    Party *vipPrev = NULL;

    
    while (vipTail != NULL && vipTail->name[0] == '*') {
        vipPrev = vipTail;
        vipTail = vipTail->next;
    }

    
    if (curr->name[0] != '*') {
        char temp[MAX_NAME];
        snprintf(temp, MAX_NAME, "*%s", curr->name);
        strncpy(curr->name, temp, MAX_NAME - 1);
        curr->name[MAX_NAME - 1] = '\0';
    }

    
    if (vipPrev == NULL) {
       
        curr->next = list->front;
        list->front = curr;
    } else {
        curr->next = vipPrev->next;
        vipPrev->next = curr;
    }

    
    if (curr->next == NULL)
        list->rear = curr;

    printf("Party '%s' has been prioritized correctly.\n", name);
}


Table* insertTable(Table *root, int id, int capacity) {
    if (capacity <= 0) {
        printf("Invalid table capacity.\n");
        return root;
    }

    if (root == NULL) {
        Table *n = (Table*)malloc(sizeof(Table));
        if (!n) {
            printf("Memory allocation failed.\n");
            return NULL;
        }
        n->id = id;
        n->capacity = capacity;
        n->occupied = 0;
        strcpy(n->occupant, "-");
        n->left = n->right = NULL;
        return n;
    }

    if (capacity < root->capacity)
        root->left = insertTable(root->left, id, capacity);
    else
        root->right = insertTable(root->right, id, capacity);

    return root;
}

Table* findSuitableTable(Table *root, int size) {
    if (!root) return NULL;

    Table *left = findSuitableTable(root->left, size);
    if (left) return left;

    if (!root->occupied && root->capacity >= size)
        return root;

    return findSuitableTable(root->right, size);
}

void seatNextParty(Waitlist *list, Table *root) {
    if (list->front == NULL) {
        printf("No parties in waitlist.\n");
        return;
    }

    Party *party = list->front;
    Table *table = findSuitableTable(root, party->size);

    if (!table) {
        printf("No suitable table available for %s (size %d).\n", party->name, party->size);
        return;
    }

    table->occupied = 1;
    strncpy(table->occupant, party->name, MAX_NAME - 1);
    table->occupant[MAX_NAME - 1] = '\0';

    printf("Seated %s (size %d) at Table %d (capacity %d)\n",
           party->name, party->size, table->id, table->capacity);

    list->front = list->front->next;
    if (!list->front) list->rear = NULL;
    free(party);
}

void inorder(Table *root) {
    if (!root) return;
    inorder(root->left);

    if (root->occupied)
        printf("Table %d | Capacity %d | Occupied by: %s\n",
               root->id, root->capacity, root->occupant);
    else
        printf("Table %d | Capacity %d | Available\n",
               root->id, root->capacity);

    inorder(root->right);
}

void freeTableById(Table *root, int id) {
    if (!root) return;

    if (root->id == id) {
        if (root->occupied) {
            root->occupied = 0;
            strcpy(root->occupant, "-");
            printf("Table %d is now available.\n", id);
        } else {
            printf("Table %d is already available.\n", id);
        }
        return;
    }

    freeTableById(root->left, id);
    freeTableById(root->right, id);
}

void freeTree(Table *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void freeWaitlist(Waitlist *list) {
    Party *temp;
    while (list->front) {
        temp = list->front;
        list->front = list->front->next;
        free(temp);
    }
    list->rear = NULL;
}