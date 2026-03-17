#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restaurant.h"

int main() {
    Table *root = NULL;
    Waitlist list;
    initWaitlist(&list);

    int numTables, choice, capacity, size;
    char name[MAX_NAME];

    printf("Enter number of tables: ");
    if (scanf("%d", &numTables) != 1 || numTables <= 0) {
        printf("Invalid number of tables.\n");
        return 1;
    }

    for (int i = 0; i < numTables; i++) {
        printf("Enter capacity of Table %d: ", i + 1);
        if (scanf("%d", &capacity) != 1 || capacity <= 0) {
            printf("Invalid capacity.\n");
            i--;
            continue;
        }
        root = insertTable(root, i + 1, capacity);
    }

    while (1) {
        printf("\n========== RESTAURANT WAITLIST SYSTEM ==========\n");
        printf("1. Add Party\n");
        printf("2. Seat Next Party\n");
        printf("3. View Waitlist\n");
        printf("4. Estimate Wait Time\n");
        printf("5. View Tables (BST)\n");
        printf("6. Free a Table\n");
        printf("7. Cancel Reservation\n");
        printf("8. Prioritize VIP Party\n");
        printf("9. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter party name: ");
                getchar();
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';

                printf("Enter party size: ");
                if (scanf("%d", &size) != 1 || size <= 0) {
                    printf("Invalid size.\n");
                    break;
                }

                addParty(&list, name, size);
                break;

            case 2:
                seatNextParty(&list, root);
                break;

            case 3:
                viewWaitlist(&list);
                break;

            case 4:
                estimateWaitTime(&list);
                break;

            case 5:
                inorder(root);
                break;

            case 6:
                {
                    int id;
                    printf("Enter table ID to free: ");
                    if (scanf("%d", &id) != 1) {
                        printf("Invalid input.\n");
                        while (getchar() != '\n');
                        break;
                    }
                    freeTableById(root, id);
                }
                break;

            case 7:
                {
                    printf("Enter party name to cancel: ");
                    getchar();
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';
                    cancelReservation(&list, name);
                }
                break;

            case 8:
                {
                    printf("Enter party name to prioritize: ");
                    getchar();
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';
                    prioritizeVIP(&list, name);
                }
                break;

            case 9:
                freeWaitlist(&list);
                freeTree(root);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}