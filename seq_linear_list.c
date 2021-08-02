#include <stdio.h>

#define MAX 4

struct element {
	int value;
};

struct seq_list {
	struct element elements[MAX];
    int size;
};

typedef struct seq_list seq_linear_list;
typedef struct element element;

void
initialize(seq_linear_list* list) {
    list->size = MAX;
}

void
show(seq_linear_list* list){
	for(int i=0; i < list->size; i++)
		printf("%d ", list->elements[i].value);
	printf("\n");
}

int
search(seq_linear_list *list, element e){
	int i = 0;

	while (i++ < list->size) {
		if(e.value == list->elements[i].value) {
			printf("It is the %d-th element.\n", i + 1);
            return i;
        }
	}
	printf("Not found!\n");
	return -1;
}

void
insert(seq_linear_list *list, element e, int index){
	if(index < 0 || index >= list->size) {
        printf("Invalid index.\n");
        return;
    }
	list->elements[index] = e;
}

int
main(void){
	seq_linear_list list;
	initialize(&list);

    element e1;
    e1.value = 9;
    insert(&list, e1, 2);
    e1.value = 7;
    insert(&list, e1, 4);

    show(&list);
    search(&list, e1);

	return 0;
}
