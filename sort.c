#include <stdio.h>

typedef int data;

int comp(data x, data y) {
    return x > y;
}

void
sort(data array[], unsigned int size, int(*comparator)(data, data)) {
    for (unsigned int i = 0; i < size-1; ++i) {
        for (unsigned j = 0; j < size-1; ++j) {
            if (comparator(array[j], array[j + 1])) {
                data tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

void
show(data array[], unsigned int size) {
    for (unsigned int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int
main(int argc, char const *argv[]) {
    data a[] = {0, 4, 8, 6, 1, 3, 2, 5, 9, 7};
    show(a, 10);
    sort(a, 10, comp);
    show(a, 10);

    return 0;
}
