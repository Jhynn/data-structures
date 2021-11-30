#include <stdio.h>

#include "search.c"

typedef int data;


void
show(data array[], unsigned int size) {
    for (unsigned int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int
comp(data x, data y) {
    return x > y;
}

void
insertion(data array[], unsigned int length, int(*comparator)(data, data)) {
	for (int i = 1; i < length; i++) {
		int j = i;

		while (j > 0 && comparator(array[j-1], array[j])) {
			int aux = array[j];
			array[j] = array[j - 1];
			array[j - 1] = aux;
			j--;                // The next, on the left, will be compared.
		}
	}
}

// Another manner.
/*
void
insertion(data array[], unsigned int length, int(*comparator)(data, data)) {
    for (int j = 1; j < length; j++) {
        data k = array[j];
        int i = j-1;

        while (i > 0 && comparator(array[i], k)) {
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = k;
    }  
}
*/
void
selection(int v[], unsigned int size, int(*comparator)(data, data)) {
	for (int i = 0; i < size; i++) {
		int m = i;

		for (int j = i + 1; j < size; j++)
			if (comparator(v[m], v[j]))
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
            if (comparator(array[j], array[j + 1])) {
                data tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
            }
        }
    }
}

void
merge(data* array, int(*comparator)(data, data), int p, int q, int r) {
  int i, j, k;
  int m = q - p + 1;
  int n = r - q;

  int left[m], right[n];

  for (i = 0; i < m; i++)
    left[i] = array[p + i];

  for (j = 0; j < n; j++)
    right[j] = array[q + 1 + j];

  i = j = 0;
  k = p;

  while (k < r) {
    if (comparator(right[j], left[i])) {
      array[k] = left[i];
      i++;
    } else {
      array[k] = right[j];
      j++;
    }
    k++;
  }
}

void
mergeSort(data* array, int(*comparator)(data, data), int p, int r) {
  if (p < r) {
    int q = (p + r) / 2; 
    mergeSort(array, comparator, p, q);
    mergeSort(array, comparator, q+1, r);

    merge(array, comparator, p, q, r);
  }
}

int
main(int argc, char const *argv[]) {
    data a[] = {0, 4, 8, 6, 1, 3, 2, 5, 9, 7};
    int s = sizeof(a) / sizeof(a[0]);

    show(a, s);

    // bubble(a, s, comp);
    // selection(a, s, comp);
    // insertion(a, s, comp);
    mergeSort(a, comp, 0, s-1);

    show(a, s);
    printf("\nThe index is %d.\n", recursiveBinarySearch(a, 0, s-1, 1));
    printf("The index is %d.\n", binarySearch(a, s, 1));

    return 0;
}
