#include <stdio.h>

#include "search.c"

typedef int data;

void
insertion(data array[], unsigned int length, int(*comparator)(data, data)) {
	for (int i = 1; i < length; i++) {
		int j = i;

		while (j > 0 && comparator(array[j], array[j-1])) {
			int aux = array[j];
			array[j] = array[j - 1];
			array[j - 1] = aux;
			j -= 1;
		}
	}
}

void
selection(int v[], unsigned int size, int(*comparator)(data, data)) {
	for (int i = 0; i < size; i++) {
		int m = i;

		for (int j = i + 1; j < size; j++)
			if (comparator(v[j], v[m]))
				m = j;

		data aux = v[i];
		v[i] = v[m];
		v[m] = aux;
	}
}

void
bubble(data array[], unsigned int size, int(*comparator)(data, data)) {
    for (unsigned int i = 0; i < size-1; ++i) {
        for (unsigned j = 0; j < size-1; ++j) {
            if (comparator(array[j + 1], array[j])) {
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
comp(data x, data y) {
    return x < y;
}

int
main(int argc, char const *argv[]) {
    data a[] = {0, 4, 8, 6, 1, 3, 2, 5, 9, 7};
    int s = sizeof(a) / sizeof(a[0]);
    show(a, 10);
    selection(a, 10, comp);
    show(a, s);
    printf("The index is %d.\n", recursiveBinarySearch(a, 0, s-1, 10));

    return 0;
}
