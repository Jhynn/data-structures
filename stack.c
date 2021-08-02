#include <stdio.h>
#include <stdlib.h>

struct element {
    int value;
    struct element* above;
};

struct stack {
    struct element* base;
    struct element* top;
    unsigned int size;
};

typedef struct element element;
typedef struct stack stack;

element*
new_element(int value) {
    element* tmp = malloc(sizeof(element));
    tmp->value = value;
    tmp->above = NULL;

    return tmp;
}

void
print_element(element* tmp) {
    printf("%d ", tmp->value);
}

void
initialize(stack* user_stack) {
    user_stack->base = NULL;
    user_stack->top  = NULL;
    user_stack->size = 0;
}

int
is_empty(stack* user_stack) {
    return !user_stack->size;
}

void
show(stack* user_stack) {
    element* aux = malloc(sizeof(element));
    aux = user_stack->base;

    printf("Size: %d\n", user_stack->size);

    while (aux) {
        print_element(aux);
        aux = aux->above;
    }
    printf("\n");
}

void
push(stack* user_stack, element* tmp) {    
    user_stack->top = tmp;
    if (is_empty(user_stack)) {
        user_stack->base = tmp;
    } else {
        element* aux = malloc(sizeof(element));
        aux = user_stack->base;
    
        while (aux->above)
            aux = aux->above;
        aux->above = tmp;
    }
    user_stack->size++;
}

void
pop(stack* user_stack) {
    if (is_empty(user_stack))
        return;
    else if (user_stack->size == 1) {
        free(user_stack->base);
        user_stack->base = NULL;
    } else {
        element* aux = malloc(sizeof(element));
        aux = user_stack->base;

        while (aux->above->above)
            aux = aux->above;

        free(aux->above);
        aux->above = NULL;
        user_stack->top = aux;
    }
    user_stack->size--;
}

int
main(int argc, char const *argv[]) {
    int number, choice;
    stack my_stack;
    initialize(&my_stack);

    do {
        printf("\t\tStack Menu\n\t1. Push \t2. Pop\n\t3. Display\t0. Exit\n");
        printf("\nEnter Choice 0─3: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                break;
            case 1:
                printf("\nPlease, enter a number: ");
                scanf("%d", &number);
                push(&my_stack, new_element(number));
                break;
            case 2:
                pop(&my_stack);
                break;
            case 3:
                printf("\n");
                show(&my_stack);
                break;
            default:
                printf("Invalid choice, please try again.\n\n");
        }
    } while (choice != 0);
    printf("Thank you!\n");

    return 0;
}
