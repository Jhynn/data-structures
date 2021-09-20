#include <stdio.h>

#define M 10

typedef int data;

int
sequentialSearch(data array[], unsigned int size, data element) {
    for (int i = 0; i < size; i++)
        if (array[i] == element)
            return i;

    return -1;
}

int
recursiveBinarySearch(data array[], int begin, int end, data element) {
    int i = (begin + end) / 2;

    if (begin > end)
        return -1;

    else if (array[i] == element)
        return i;

    else if (array[i] < element)
        return recursiveBinarySearch(array, i + 1, end, element);

    else
        return recursiveBinarySearch(array, begin, i - 1, element);
}

int
binarySearch(data array[], unsigned int size, data element) {
    int begin = 0;
    int end   = size - 1;

    while (begin <= end) {
        int i = (begin + end) / 2;

        if (array[i] == element)
            return i;

        else if (array[i] < element)  // The element is on the right side.
            begin = i + 1;

        // Otherwise the element is on the left side, i.e., vector[i] > element.
        else
            end = i;
    }

    return -1;
}

/*
int
main(void) {
    // The array must be ordered (for binary search).
    int vector[M] = {7, 10, 29, 37, 41, 50, 69, 79, 87, 91};
    int v;

    for (int i = 0; i < M; i++) {
        v = vector[i];

        printf("Sequential searching\t  %d: \t%d\n", v,
               sequentialSearch(vector, M, v));

        printf("(Iterative) binary search %d: \t%d\n", v,
               binarySearch(vector, M, v));

        printf("Recursive binary search   %d: \t%d\n", v,
               recursiveBinarySearch(vector, 0, M - 1, v));

        printf("\n");
    }

    return 0;
}
*/