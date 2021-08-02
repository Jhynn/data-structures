#include <stdio.h>
#include <stdlib.h>

struct element {
    int value;
    struct element* next;
};

struct queue {
    struct element* first;
    unsigned int size;
};

typedef struct element element;
typedef struct queue queue;

element*
new_element(int value) {
    element* tmp = malloc(sizeof(element));
    tmp->value = value;
    tmp->next  = NULL;

    return tmp;
}

void
print_element(element* tmp) {
    printf("%d ", tmp->value);
}

void
initialize(queue* user_queue) {
    user_queue->first = NULL;
    user_queue->size  = 0;
}

int
is_empty(queue* user_queue) {
    return !user_queue->size;
}

void
show(queue* user_queue) {
    element* aux = malloc(sizeof(element));
    aux = user_queue->first;

    printf("Size: %d\n", user_queue->size);

    while (aux) {
        print_element(aux);
        aux = aux->next;
    }
    printf("\n");
}

void
enqueue(queue* user_queue, element* tmp) {    
    if (is_empty(user_queue)) {
        user_queue->first = tmp;
    } else {
        element* aux = malloc(sizeof(element));
        aux = user_queue->first;
    
        while (aux->next)
            aux = aux->next;
        aux->next = tmp;
    }
    user_queue->size++;
}

void
dequeue(queue* user_queue) {
    if (is_empty(user_queue))
        return;

    element* aux = malloc(sizeof(element));
    aux = user_queue->first->next;

    free(user_queue->first);
    user_queue->first = NULL;
    user_queue->first = aux;

    user_queue->size--;
}

int
main(int argc, char const *argv[]) {
    int number, choice;
    queue my_queue;
    initialize(&my_queue);

    do {
        printf("\t\tQueue Menu\n\t1. Enque \t2. Deque\n\t3. Display\t0. Exit\n");
        printf("\nEnter Choice 0─3: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                break;
            case 1:
                printf("\nPlease, enter a number: ");
                scanf("%d", &number);
                enqueue(&my_queue, new_element(number));
                break;
            case 2:
                dequeue(&my_queue);
                break;
            case 3:
                printf("\n");
                show(&my_queue);
                break;
            default:
                printf("Invalid choice, please try again.\n\n");
        }
    } while (choice != 0);
    printf("Thank you!\n");

    return 0;
}
