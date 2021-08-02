#include <stdio.h>
#include <stdlib.h>

struct element {
    int data;
    struct element* previous;
    struct element* next;
};

struct doubly_linked_list {
    struct element* first;
    struct element* last;
    unsigned int size;
};

typedef struct element element;
typedef struct doubly_linked_list list;

void
initialize(list* user_list) {
    user_list->first = NULL;
    user_list->last  = NULL;
    user_list->size  = 0;
}

element*
new_element(int value) {
    element* tmp  = malloc(sizeof(element));
    tmp->previous = NULL;
    tmp->next = NULL;
    tmp->data = value;

    return tmp;
}

void
print_element(element* user_element) {
    printf("%d ", user_element->data);
}

void
add_in_the_end(list* user_list, element* member) {
    if (!user_list->size) {
        user_list->first = member;
        user_list->last  = member;

        user_list->first->next = user_list->last;
        user_list->last->next = user_list->first;
        user_list->first->previous = user_list->last;
        user_list->last->previous = user_list->first;
    } else {
        member->next = user_list->first;
        user_list->first->previous = member;
        user_list->last->next = member;
        member->previous = user_list->last;
        user_list->last = member;
    }
    user_list->size++;
}

void
add_in_the_begin(list* user_list, element* member) {
    if (!user_list->size) {
        user_list->first = member;
        user_list->last  = member;

        user_list->first->next = user_list->last;
        user_list->last->next = user_list->first;
        user_list->first->previous = user_list->last;
        user_list->last->previous = user_list->first;
    } else {
        member->next = user_list->first;
        member->previous = user_list->last;
        user_list->first->previous = member;
        user_list->last->next = member;
        user_list->first = member;
    }
    user_list->size++;
}

void
insert(list* user_list, element* member, int position) {
    if (!user_list->size || position == 1)
        add_in_the_begin(user_list, member);
    else if (position == user_list->size + 1)
        add_in_the_end(user_list, member);
    else if (position < 1 || position > user_list->size)
        printf("Invalid position\n");
    else {
        element* aux = malloc(sizeof(struct element));        
        unsigned int half = (int) user_list->size / 2;

        if (position <= half) {
            aux = user_list->first;

            for (unsigned int i = 2; i < half; i++) {
                aux = aux->next;
            }
            member->next = aux->next;
            aux->next->previous = member;
            member->previous = aux;
            aux->next = member;
        } else {
            aux = user_list->last;

            for (unsigned int i = user_list->size - 1; i > position; i--) {
                aux = aux->previous;
            }
            member->next = aux;
            member->previous = aux->previous;
            aux->previous->next = member;
            aux->previous = member;
        }
        user_list->size++;
    }
}

void
show(list* user_list) {
    printf("Size: %d\n", user_list->size);

    if (!user_list->size) return;

    unsigned int counter = 0;
    element* aux = malloc(sizeof(element));
    aux = user_list->first;

    while (counter++ < user_list->size) {
        print_element(aux);
        aux = aux->next;
    }
    printf("\n");
}

void
delete(list* user_list, int position) {
    if (!user_list->size) {
        printf("The list is empty.");
        return;
    } else if (user_list->size == 1 && position == 1) {
        free(user_list->first);
        user_list->first = NULL;
    } else if (position < 1 || position > user_list->size) {
        printf("Invalid position\n");
        return;
    } else {
        if (position == 1) {
            user_list->last->next = user_list->first->next;
            user_list->first->next->previous = user_list->last;
            free(user_list->first);
            user_list->first = NULL;
            user_list->first = user_list->last->next;
        } else if (position == user_list->size) {
            user_list->first->previous = user_list->last->previous;
            user_list->last->previous->next = user_list->first;
            free(user_list->last);
            user_list->last = NULL;
            user_list->last = user_list->first->previous;
        } else {
            element* aux = malloc(sizeof(struct element));     
            unsigned int half = (int) user_list->size / 2;

            if (position <= half) {
                aux = user_list->first;

                for (unsigned int i = 2; i < half; i++) {
                    aux = aux->next;
                }
                element* tmp = malloc(sizeof(struct element));     
                tmp = aux->next;
                aux->next = aux->next->next;
                aux->next->previous = aux;
                free(tmp);
                tmp = NULL;
            } else {
                aux = user_list->last;

                for (unsigned int i = user_list->size - 1; i > position; i--) {
                    aux = aux->previous;
                }
                element* tmp = malloc(sizeof(struct element));     
                tmp = aux->previous;
                aux->previous = aux->previous->previous;
                aux->previous->next = aux;
                free(tmp);
                tmp = NULL;
            }
        }
    }
    user_list->size--;
}

int
main(int argc, char const *argv[]) {
    int number, choice, position;
    list my_list;

    initialize(&my_list);

    do {
        printf("\t\tDoubly Linked List Menu\n\n\t1. Add in the begin"
                "\t\t2. Add in the end\n\t3. Insert into"
                "\t4. Display\t5. Remove\t0. Exit\n");
        printf("\nEnter Choice 0─3: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                break;
            case 1:
                printf("\nPlease, enter a number: ");
                scanf("%d", &number);
                add_in_the_begin(&my_list, new_element(number));
                break;
            case 2:
                printf("\nPlease, enter a number: ");
                scanf("%d", &number);
                add_in_the_end(&my_list, new_element(number));
                break;
            case 3:
                printf("\nPlease, enter a number: ");
                scanf("%d", &number);
                printf("\nPlease, enter the position: ");
                scanf("%d", &position);
                insert(&my_list, new_element(number), position);
                break;
            case 4:
                printf("\n\n");
                show(&my_list);
                break;
            case 5:
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
