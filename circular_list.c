#include <stdio.h>
#include <stdlib.h>

struct element {
    int data;
    struct element* next;
};

struct circular_list {
    struct element* reference;
    unsigned int size;
};

typedef struct element element;
typedef struct circular_list circular_list;

void
initialize(circular_list* user_list) {
    user_list->reference = NULL;
    user_list->size = 0;
}

element*
new_element(int value) {
    element* tmp = malloc(sizeof(element));
    tmp->next = NULL;
    tmp->data = value;

    return tmp;
}

void
print_element(element* user_element) {
    printf("%d ", user_element->data);
}

void
insert(circular_list* user_list, element* member) {
    if (!user_list->size) {
        user_list->reference = member;
    } else {
        if (user_list->size == 1) {
            user_list->reference->next = member;
            member->next = user_list->reference;
        } else {
            element* aux = malloc(sizeof(element));
            aux = user_list->reference->next;
            unsigned int counter = 1;

            while (++counter != user_list->size) {
                aux = aux->next;
            }
            aux->next = member;
            member->next = user_list->reference;
        }
    }
    user_list->size++;
}

void
show(circular_list* user_list, unsigned int times) {
    printf("Size: %d\n", user_list->size);
    if (!user_list->size) {
        printf("The list is empty!");
    } else if (user_list->size == 1) {
        for (unsigned int i = 0; i < times; i++) {
            print_element(user_list->reference);
        }
    } else {
        times *= user_list->size;
        element* aux = malloc(sizeof(element));
        aux = user_list->reference;
        unsigned int counter = 0;

        while (counter++ != times) {
            print_element(aux);
            aux = aux->next;
        }
    }
    printf("\n");
}

void
delete(circular_list* user_list, int position) {
    if (!user_list->size) {
        printf("The list is empty!");
        return;
    } else if (position < 1 || position > user_list->size) {
        printf("Invalid position!\n");
        return;
    } else if (position == 1 && user_list->size < 3) {
        if (user_list->size == 1) {
            free(user_list->reference);
            user_list->reference = NULL;
        } else if (user_list->size == 2) {
            user_list->reference = user_list->reference->next;
            free(user_list->reference->next);
            user_list->reference->next = NULL;
        }
    } else {
        unsigned int counter = 1;
        element* aux = malloc(sizeof(element));
        element* tmp = malloc(sizeof(element));
        aux = user_list->reference;

        unsigned int proper = position - 1;

        if (position == 1)
            proper = user_list->size;

        while (counter++ != proper)
            aux = aux->next;

        tmp = aux->next->next;
        free(aux->next);
        aux->next = NULL;
        aux->next = tmp;
        if (position == 1)
            user_list->reference = tmp;
        tmp = NULL;
    }
    user_list->size--;
}

int
main(void) {
    int number, choice, position, times;
    circular_list my_list;

    initialize(&my_list);

    do {
        printf("List Menu\n\t1. Insert\t2. Display\n"
                "\t3. Remove\t0. Exit\n");
        printf("\nEnter Choice 0─3: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                break;
            case 1:
                printf("\nPlease, enter a number: ");
                scanf("%d", &number);
                insert(&my_list, new_element(number));
                break;
            case 2:
                printf("\nHow many times: ");
                scanf("%d", &times);
                printf("\n");
                show(&my_list, times);
                break;
            case 3:
                printf("Please, enter the position: ");
                scanf("%d", &position);
                delete(&my_list, position);
                break;
            default:
                printf("Invalid choice, please try again.\n\n");
        }
    } while (choice != 0);
    printf("Thank you!\n");
}
