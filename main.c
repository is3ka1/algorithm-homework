#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef DEBUG 
    #define DEBUG 1
#endif

#if DEBUG
    #define debug_log(array) printA(array)
#else
    #define debug_log(array)  
#endif


typedef struct IntArray {
    int *head;
    unsigned int len;
} Array;

void printA(Array array) {
    for (unsigned int i = 0; i < array.len; i++) {
        printf("%4d ", array.head[i]);
    }
    printf("\n");
}

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void exchange_sort(Array array) {
    for (int i = 0; i < array.len - 1; i++) {
        for (int j = i + 1; j < array.len; j++) {
            if (array.head[j] < array.head[i]) {
                swap(array.head + i, array.head + j);
                debug_log(array);
            }
        }
    }
}

void merge(Array a1, Array a2) {
    int j = 0, k = 0, index = 0;
    int *tmpA = (int *)malloc(sizeof(int) * (a1.len + a2.len));

    while (j < a1.len && k < a2.len) {
        if (a1.head[j] < a2.head[k]) {
            tmpA[index++] = a1.head[j++];
        } else {
            tmpA[index++] = a2.head[k++];
        }
    }
    if (k >= a2.len) {
        for (int i = j; i < a1.len; i++) {
            tmpA[index++] = a1.head[i];
        }
    } 

    for (int i = 0; i < index; i++) {
        if (i < a1.len) {
            a1.head[i] = tmpA[i];
        } else {
            a2.head[i - a1.len] = tmpA[i];
        } 
    }
    free(tmpA);
}

void merge_sort(Array array) {
    if (array.len <= 1) {
        return;
    }

    Array left = {
        .head = array.head,
        .len = array.len / 2
    };
    Array right = {
        .head = array.head + left.len,
        .len = array.len - left.len
    };
    merge_sort(left);
    merge_sort(right);
    merge(left, right);
    debug_log(array);
}

void partition(Array array, Array *left, Array *right) {
    int pivotitem = array.head[0];
    int j = 0;
    for (int i = 1; i < array.len; i++) {
        if (array.head[i] < pivotitem) {
            swap(array.head + i, array.head + ++j);
        }
    }
    swap(array.head, array.head + j);

    *left = (Array) {
        .head = array.head,
        .len = j
    };
    *right = (Array) {
        .head = array.head + j + 1,
        .len = array.len - j - 1
    };
}

void quick_sort(Array array) {
    if (array.len <= 1) {
        return;
    }
    Array right, left;
    partition(array, &left, &right);
    quick_sort(left);
    quick_sort(right);
    debug_log(array);
}

void counting_sort(Array array, int min, int max) {
    unsigned int index = 0; 
    unsigned short *count = calloc(max - min + 1, sizeof(unsigned short));
    for (int i = 0; i < array.len; i++) {
        count[array.head[i] - min]++;
    }
    for (int i = 0; i < max - min + 1; i++) {
        while (count[i]--) {
            array.head[index++] = min + i;
            debug_log(array);
        }
    }
    free(count);
}

void uniform_cs_data(Array *array, int min, int max) {
    array->head = (int *)realloc(array->head, sizeof(int) * (array->len + 2));
    array->head[array->len] = min;
    array->head[array->len + 1] = max;
}

void uniform_counting_sort(Array array) {
    counting_sort(array, array.head[array.len], array.head[array.len + 1]);
}

void heapify(Array array, unsigned int node) {
    unsigned int left_child = node * 2 + 1, right_child = node * 2 + 2;
    while (left_child < array.len) {
        unsigned int max_node = (array.head[left_child] > array.head[node]) ? left_child : node;
        if (right_child < array.len && array.head[right_child] > array.head[max_node]) {
            max_node = right_child;
        }
        if (node == max_node) {
            break;
        }
        swap(array.head + node, array.head + max_node);
        node = max_node;
        left_child = node * 2 + 1;
        right_child = node * 2 + 2;
    }
}

void heap_sort(Array array) {
    unsigned int len = array.len;
    for (int i = array.len / 2 - 1; i >= 0; i--) {
        heapify(array, i);
    }
    for (unsigned int i = array.len - 1; i > 0; i--) {
        swap(array.head, array.head + i);
        array.len--;
        heapify(array, 0);
        debug_log(((Array) { .head = array.head, .len = len }));
    }
}

Array newArray(unsigned int size) {
    return (Array) {
        .head = (int *)malloc(sizeof(int) * size),
        .len = size
    };
}

void ascending_init(Array array) {
    for (int i = 0; i < array.len; i++) {
        array.head[i] = i + 1;
    }
}

void descending_init(Array array) {
    for (int i = 0; i < array.len; i++) {
        array.head[i] = array.len - i;
    }
}

void random_init(Array array, int min, int max) {
    srand(time(NULL));
    for (int i = 0; i < array.len; i++) {
        array.head[i] = rand() % (max - min + 1) + min;
    }
}

void calculate_cost(int seq_size, int min, int max, int algo, int stdin_mode, double *costs) {
    Array ascending_array = newArray(seq_size);
    ascending_init(ascending_array);

    Array descending_array = newArray(seq_size);
    descending_init(descending_array);

    Array random_array = newArray(seq_size);
    random_init(random_array, min, max);

    void (*sort)(Array);

    switch (algo) {
    case 1:
        sort = exchange_sort;
        break;
    case 2:
        sort = merge_sort;
        break;
    case 3:
        sort = quick_sort;
        break;
    case 4:
        uniform_cs_data(&ascending_array, 0, seq_size);
        uniform_cs_data(&descending_array, 0, seq_size);
        uniform_cs_data(&random_array, min, max);
        sort = uniform_counting_sort;
        break;
    case 5:
        sort = heap_sort;
        break;
    default:
        break;
    }

    double cost;
    clock_t time_records[10];
    char *array_names[] = {"ascending", "descending", "random"};
    Array arrays[] = {ascending_array, descending_array, random_array};

    for (int i = 0, t = 0 ; i < 3; i++) {
        if (stdin_mode) {
            printf("original %s sequence: \n", array_names[i]);
            printA(arrays[i]);
            if (DEBUG) {
                printf("steps: \n");
            }
        }
        time_records[t++] = clock();
        sort(arrays[i]);
        time_records[t++] = clock();
        cost = ((double) (time_records[t - 1] - time_records[t - 2])) / CLOCKS_PER_SEC;

        if (stdin_mode) {
            printf("sorted %s sequence: \n", array_names[i]);
            printA(arrays[i]);
            printf("cost time: %f sec\n--------------------\n\n", cost);
        } else {
            costs[i] = cost;
        }
    }

}

void run_by_stdin() {
    unsigned int seq_size;
    int MAX, MIN;
    int algo;

    printf("Enter sequence size: ");
    scanf("%ud", &seq_size);
    printf("Enter sequence element smallest range: ");
    scanf("%d", &MIN);
    printf("Enter sequence element biggest range: ");
    scanf("%d", &MAX);
    printf("\n");

    printf("1) exchange_sort\n2) merge_sort\n3) quick_sort\n4) counting_sort\n5) heap_sort\nalgorithm: ");
    scanf("%d", &algo);
    printf("\n");

    calculate_cost(seq_size, MIN, MAX, algo, 1, NULL);
}

int main(int argc, char const *argv[]) {
    if (DEBUG) {
        printf("Debug Logs [On]\n\n");
    }

    if (argc == 1) {
        run_by_stdin();
    } else if (argc == 5) {
        int seq_size = atoi(argv[1]);
        int min = atoi(argv[2]);
        int max = atoi(argv[3]);
        int algo = atoi(argv[4]);
        double costs[3];
        calculate_cost(seq_size, min, max, algo, 0, costs);
        printf("%d,%f,%f,%f\n", seq_size, costs[0], costs[1], costs[2]);
    }
    return 0;
}
