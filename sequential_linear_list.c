#include <stdio.h>
#include <stdlib.h>

struct element {
	int value;
};

struct seq_list {
	struct element** head;
	unsigned int size;
};

typedef struct seq_list seq_linear_list;
typedef struct element element;

element*
new_element(int value) {
    element* aux = malloc(sizeof(element));
    aux->value = value;

    return aux;
}

void
show_element(element* member) {
    if (member != NULL)
        printf("%d\n", member->value);
    else
        printf("Not used.\n");
}

void
initialize(seq_linear_list* list, unsigned int size) {
    list->size = size;
    list->head = calloc(size, sizeof(element*));
}

void
show(seq_linear_list* list) {
    for (int i = 0; i < list->size; i++) {
        show_element(*(list->head + i));
    }
    printf("\n");
}

void
insert(seq_linear_list* list, element* member, int index) {
    if (index < 0 || index > list->size) {
        printf("Invalid index!\n");
        return;
    } else {
        *(list->head + index) = member;
    }
}

void
delete(seq_linear_list* list, int index) {
    if (index < 0 || index > list->size) {
        printf("Invalid index!\n");
        return;
    } else if (*(list->head + index) != NULL) {
        // free((*(list->head + index)));
        *(list->head + index) = NULL;
    }
}

int
search(seq_linear_list* list, int value) {
    int i = 0;
    for (; i < list->size; i++) {
        if (*(list->head + i) != NULL && (*(list->head + i))->value == value) {
            printf("It is the %d-th element.\n", i + 1);
            return i;
        }
    }
    printf("Not found!\n");
    return -1;
}

int
main(int argc, char const *argv[]) {
    int number, choice, position;
    seq_linear_list my_list;

    do {
        printf("\t\tLinear Sequential List Menu\n"
                "\t1. What is the size of the list? \n"
                "\t2. Insert\t3. Remove\n"
                "\t4. Display\t5. Search\t0. Exit\n");
        printf("\nEnter Choice 0─3: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                break;
            case 1:
                printf("\nPlease, enter a number: ");
                scanf("%d", &number);
                initialize(&my_list, number);
                break;
            case 2:
                printf("\nPlease, enter a number: ");
                scanf("%d", &number);
                printf("Please, enter the position: ");
                scanf("%d", &position);
                insert(&my_list, new_element(number), position - 1);
                break;
            case 3:
                printf("Please, enter the position: ");
                scanf("%d", &position);
                delete(&my_list, position - 1);
                break;
            case 4:
                printf("\n");
                show(&my_list);
                break;
            case 5:
                printf("Please, enter a number: ");
                scanf("%d", &number);
                search(&my_list, number);
                printf("\n");
                break;
            default:
                printf("Invalid choice, please try again.\n\n");
        }
    } while (choice != 0);
    printf("Thank you!\n");

    return 0;
}
