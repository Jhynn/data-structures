#include <stdio.h>
#include <stdlib.h>

struct element {
    int data;
    struct element* next;
};

struct singly_linked_list {
    struct element* head;
    unsigned int size;
};

typedef struct element element;
typedef struct singly_linked_list list;

void
initialize(list* user_list) {
    user_list->head = NULL;
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
add_in_the_end(list* user_list, element* member) {
    if (!user_list->size) {
        user_list->head = member;
    } else {
        element* aux = malloc(sizeof(element));
        aux = user_list->head;

        while (aux->next)
            aux = aux->next;

        aux->next = member;

    }
    user_list->size++;
}

void
add_in_the_begin(list* user_list, element* member) {
    if (!user_list->size) {
        user_list->head = member;
    } else {
        member->next = user_list->head;
        user_list->head = member;
    }
    user_list->size++;
}

void
insert(list* user_list, element* member, int position) {
    if (!user_list->size || position == 1)
        add_in_the_begin(user_list, member);
    else if (position == user_list->size + 1)
        add_in_the_end(user_list, member);
    else if (position > user_list->size || position < 1)
        printf("Invalid position\n");
    else {
        element* aux = malloc(sizeof(struct element));        
        aux = user_list->head;
        unsigned int index = 1;

        while (++index != position)
            aux = aux->next;

        member->next = aux->next;
        aux->next = member;
        user_list->size++;
    }
}

void
show(list* user_list) {
    printf("Size: %d\n", user_list->size);

    if (!user_list->size) return;

    element* aux = malloc(sizeof(element));
    aux = user_list->head;

    while (aux) {
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
        free(user_list->head);
        user_list->head = NULL;
    } else if (position < 1 || position > user_list->size) {
        printf("Invalid position\n");
    } else {
        element* tmp = malloc(sizeof(element));
        if (position == 1) {
            tmp = user_list->head->next;
            free(user_list->head);
            user_list->head = NULL;
            user_list->head = tmp;
        } else {
            unsigned int index = 1;
            element* aux = malloc(sizeof(element));
            aux = user_list->head;
    
            while (++index != position)
                aux = aux->next;
            
            tmp = aux->next->next;
            free(aux->next);
            aux->next = NULL;
            aux->next = tmp;
        }
    }
    user_list->size--;
}

int
main(void) {
    int number, choice, position;
    list my_list;

    initialize(&my_list);

    do {
        printf("List Menu\n\t1. Add in the begin\n"
                "\t2. Add in the end\t3. Insert into\n"
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
                printf("\n");
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
