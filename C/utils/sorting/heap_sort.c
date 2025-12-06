#include "heap_sort.h"

static void build_heap(int *array, int size);
static void heapify(int *array, int n, int i);
static int left(int i);
static int right(int i);
static int parent(int i);
static void swap(int *array, int i, int j);

void heap_sort(int *array, int size)
{
    build_heap(array, size);
    for (int i = size - 1; i > 0; --i) {
        swap(array, 0, i);
        heapify(array, i, 0);
    }
}

static void build_heap(int *array, int size) {
    for (int i = parent(size - 1); i > -1; --i) {
        heapify(array, size, i);
    }
}

static void heapify(int *array, int n, int i) {
    int l = left(i);
    int r = right(i);

    int max_index = i;

    if (l < n && array[l] > array[max_index]) {
        max_index = l;
    }

    if (r < n && array[r] > array[max_index]) {
        max_index = r;
    }

    if (max_index != i) {
        swap(array, max_index, i);
        heapify(array, n, max_index);
    }
}

static int left(int i) {
    return 2 * i + 1;
}

static int right(int i) {
    return 2 * i + 2;
}

static int parent(int i) {
    return (i - 1) / 2;
}

static void swap(int *array, int i, int j) {
    int buffor = array[i];
    array[i] = array[j];
    array[j] = buffor;
}
